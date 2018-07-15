#include "loadobj.h"

#include <fstream>
#include <iostream>

namespace load_obj
{   
    
    loaded_obj LoadObj(const char* FilePath)
    {
        loaded_obj Result = {};
        
        int LastTempVertIndex = 0;
        int LastTempUVsIndex = 0;
        int LastTempNormalsIndex = 0;
        
        V3 TempVertices[TEMP_BUFFER_SIZE] = {};
//        V2 TempUVs[TEMP_BUFFER_SIZE] = {};
//        V3 TempNormals[TEMP_BUFFER_SIZE] = {};
                
        int LastTempVertIndiceIndex = 0;
        int LastTempUVsIndiceIndex = 0;
        int LastTempNormalsIndiceIndex = 0;
        
        int TempVerticeIndices[TEMP_BUFFER_SIZE] = {};
//        int TempUVsIndices[TEMP_BUFFER_SIZE] = {};
//        int TempNormalsIndices[TEMP_BUFFER_SIZE] = {};
        
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
                        TempVertices[LastTempVertIndex].X = Temp[0];
                        TempVertices[LastTempVertIndex].Y = Temp[1];
                        TempVertices[LastTempVertIndex++].Z = Temp[2];
                        
                    }
                    else if(strcmp(Line, VERTEX_TEXTURE_COORDINATE) == 0)
                    {
                        float Temp[2] = {};
                        fscanf(File, "%f %f", &Temp[0], &Temp[1]);
//                        TempUVs[LastTempUVsIndex].X = Temp[0];
//                        TempUVs[LastTempUVsIndex++].Y = Temp[1];
                    }
                    else if(strcmp(Line, VERTEX_NORMAL) == 0)
                    {                        
                        float Temp[3] = {};
                        fscanf(File, "%f %f %f", &Temp[0], &Temp[1], &Temp[2]);                        
//                        TempNormals[LastTempNormalsIndex].X = Temp[0];
//                        TempNormals[LastTempNormalsIndex].Y = Temp[1];
//                        TempNormals[LastTempNormalsIndex++].Z = Temp[2];
                    }
                    else if(strcmp(Line, VERTEX_FACE) == 0)
                    {   
                        
                        int Test[9] = {};
                        const int TriangleMatches = fscanf(File, " %d/%d/%d %d/%d/%d %d/%d/%d\n", &Test[0],&Test[1],&Test[2],&Test[3],&Test[4],&Test[5],&Test[6],&Test[7],&Test[8]); 
                        
                        if(TriangleMatches != TRIANGLE_FACE_MATCH_COUNT)
                        {
                            SDL_Log("Incorrect number of faces in Obj %s", FilePath);
                            fclose(File);
                            
                            loaded_obj FailedResult = {};
                            return FailedResult;   
                        }                        
                        
                        TempVerticeIndices[LastTempVertIndiceIndex++] = Test[0];
                        TempVerticeIndices[LastTempVertIndiceIndex++] = Test[3];
                        TempVerticeIndices[LastTempVertIndiceIndex++] = Test[6];
                        
                        //TempUVsIndices[LastTempUVsIndiceIndex++] = Test[1];
                       // TempUVsIndices[LastTempUVsIndiceIndex++] = Test[4];
                        //TempUVsIndices[LastTempUVsIndiceIndex++] = Test[7];
                        
                       // TempNormalsIndices[LastTempNormalsIndiceIndex++] = Test[2];
                        //TempNormalsIndices[LastTempNormalsIndiceIndex++] = Test[5];
                        //TempNormalsIndices[LastTempNormalsIndiceIndex++] = Test[8];
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
        
        // 
        
        V3 FinalVertex[TEMP_BUFFER_SIZE] = {};
        int FinalVertexIndex = 0;
        for(int IndiceIndex = 0; IndiceIndex < LastTempVertIndiceIndex; ++IndiceIndex)
        {
            int VertexIndex = TempVerticeIndices[IndiceIndex];            
            FinalVertex[FinalVertexIndex++] = TempVertices[VertexIndex - 1];
        }
        
        Result.Vertices.Vertex = (V3*)PlatformAlloc(sizeof(V3) * FinalVertexIndex);
        Result.Vertices.Vertex = FinalVertex;
        Result.Vertices.VertexSize = sizeof(V3) * FinalVertexIndex;
        Result.Vertices.IndiceCount = FinalVertexIndex;
        
        fclose(File);
        return Result;
    }
};