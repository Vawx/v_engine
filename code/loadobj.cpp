#include "loadobj.h"

#include <fstream>
#include <iostream>

namespace load_obj
{           
    // Stores vertex, uv, normals
    static V3 TempVertex[TEMP_BUFFER_SIZE] = {};
    static V2 TempUV[TEMP_BUFFER_SIZE] = {};
    static V3 TempNormal[TEMP_BUFFER_SIZE] = {};
    
    static int TempVertexIndex = 0;
    static int TempUVIndex = 0;
    static int TempNormalIndex = 0;
    
    static face_data FaceData[TEMP_BUFFER_SIZE] = {};
    static int FaceDataVertexIndex = 0;
    static int FaceDataUVIndex = 0;
    static int FaceDataNormalIndex = 0;
        
    static V3 FinalVertex[TEMP_BUFFER_SIZE] = {};
    static V2 FinalUV[TEMP_BUFFER_SIZE] = {};
    static V3 FinalNormal[TEMP_BUFFER_SIZE] = {};
    
    static int FinalVertexIndex = 0;
    static int FinalUVIndex = 0;
    static int FinalNormalIndex = 0;
        
    loaded_obj LoadObj(const char* FilePath)
    {
        loaded_obj Result = {};
        
        FILE* File = fopen(FilePath, "r");
        if(File)
        {
            while(1)
            {
                char Line[128] = {};
                int Res = fscanf(File, "%s", Line);
                if(Res != EOF)
                {
                    if(strcmp(Line, OBJECT_NAME) == 0)
                    {                        
                        if(Result.ObjectName == nullptr)
                        {
                            char Name[1024] = {};
                            int NameLength = fscanf(File, "%s", &Name);
                            
                            const int NameCopyLength = strlen(Name) + 1;                            
                            Result.ObjectName = new char(NameCopyLength);
                            Result.ObjectName = Name;
                        }
                    }
                    else if(strcmp(Line, VERTEX) == 0)
                    {
                        float Temp[3] = {};
                        fscanf(File, "%f %f %f", &Temp[0], &Temp[1], &Temp[2]);                        
                        TempVertex[TempVertexIndex].X = Temp[0];
                        TempVertex[TempVertexIndex].Y = Temp[1];
                        TempVertex[TempVertexIndex++].Z = Temp[2];                        
                    }
                    else if(strcmp(Line, VERTEX_TEXTURE_COORDINATE) == 0)
                    {
                        float Temp[2] = {};
                        fscanf(File, "%f %f", &Temp[0], &Temp[1]);
                        
                        TempUV[TempUVIndex].X = Temp[0];
                        TempUV[TempUVIndex++].Y = Temp[1];
                    }
                    else if(strcmp(Line, VERTEX_NORMAL) == 0)
                    {                        
                        float Temp[3] = {};
                        fscanf(File, "%f %f %f", &Temp[0], &Temp[1], &Temp[2]);    
                        
                        TempNormal[TempNormalIndex].X = Temp[0];
                        TempNormal[TempNormalIndex].Y = Temp[1];
                        TempNormal[TempNormalIndex++].Z = Temp[2];
                    }
                    else if(strcmp(Line, VERTEX_FACE) == 0)
                    {   
                        int Temp[9] = {};
                        const int TriangleMatches = fscanf(File, " %d/%d/%d %d/%d/%d %d/%d/%d\n", &Temp[0],&Temp[1],&Temp[2],&Temp[3],&Temp[4],&Temp[5],&Temp[6],&Temp[7],&Temp[8]); 
                        
                        if(TriangleMatches != TRIANGLE_FACE_MATCH_COUNT)
                        {
                            SDL_Log("Incorrect number of faces in Obj %s", FilePath);
                            fclose(File);
                            
                            loaded_obj FailedResult = {};
                            return FailedResult;   
                        }        
                        
                        FaceData[FaceDataVertexIndex++].Vertex = Temp[0];
                        FaceData[FaceDataVertexIndex++].Vertex = Temp[3];
                        FaceData[FaceDataVertexIndex++].Vertex = Temp[6];
                                                
                        FaceData[FaceDataUVIndex++].UV = Temp[1];
                        FaceData[FaceDataUVIndex++].UV = Temp[4];
                        FaceData[FaceDataUVIndex++].UV = Temp[7];
                        
                        FaceData[FaceDataNormalIndex++].Normal = Temp[2];
                        FaceData[FaceDataNormalIndex++].Normal = Temp[5];
                        FaceData[FaceDataNormalIndex++].Normal = Temp[8];
                    }
                } 
                else
                {
                    break;
                }                
            }
        }
        else
        {            
            SDL_Log("Failed to open OBJ File at: %s, because %s", FilePath, strerror(errno));
            return Result;
        }
            
        const int MedianIndexCount = (FaceDataVertexIndex + FaceDataUVIndex + FaceDataNormalIndex) / 3;
        Assert(FaceDataVertexIndex == MedianIndexCount && FaceDataUVIndex == MedianIndexCount && FaceDataNormalIndex == MedianIndexCount);
        
        // Loop all faces and pull Vertex, UV, and Normals.
        for(int IndiceIndex = 0; IndiceIndex < FaceDataVertexIndex; ++IndiceIndex)
        {
            unsigned int VertexIndex = FaceData[IndiceIndex].Vertex;
            unsigned int UVIndex = FaceData[IndiceIndex].UV;
            unsigned int NormalIndex = FaceData[IndiceIndex].Normal;
            
            FinalVertex[FinalVertexIndex++] = TempVertex[VertexIndex - 1];
            FinalUV[FinalUVIndex++] = TempUV[UVIndex - 1];
            FinalNormal[FinalNormalIndex++] = TempNormal[NormalIndex - 1];
        }
        
        Result.Data = {};
        const int VertexSize = sizeof(V3) * FinalVertexIndex;
        Result.Data.Vertex = (V3*)PlatformAlloc(VertexSize);
        Result.Data.Vertex = FinalVertex;
        Result.Data.VertexSizeCount.Count = FinalVertexIndex;
        Result.Data.VertexSizeCount.Size = VertexSize;
        
        const int UVSize = sizeof(V2) * FinalUVIndex;
        Result.Data.UV = (V2*)PlatformAlloc(UVSize);
        Result.Data.UV = FinalUV;
        Result.Data.UVSizeCount.Count = FinalUVIndex;
        Result.Data.UVSizeCount.Size = UVSize;
        
        const int NormalSize = sizeof(V3) * FinalNormalIndex;
        Result.Data.Normal = (V3*)PlatformAlloc(NormalSize);
        Result.Data.Normal = FinalNormal;
        Result.Data.NormalSizeCount.Count = FinalNormalIndex;
        Result.Data.NormalSizeCount.Size = NormalSize;
                
        fclose(File);
        return Result;
    }
};
