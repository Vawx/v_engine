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
        V2 TempUVs[TEMP_BUFFER_SIZE] = {};
        V3 TempNormals[TEMP_BUFFER_SIZE] = {};
                
        int LastTempVertIndiceIndex = 0;
        int LastTempUVsIndiceIndex = 0;
        int LastTempNormalsIndiceIndex = 0;
        
        unsigned int TempVerticeIndices[TEMP_BUFFER_SIZE] = {};
        unsigned int TempUVsIndices[TEMP_BUFFER_SIZE] = {};
        unsigned int TempNormalsIndices[TEMP_BUFFER_SIZE] = {};
        
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
                        V3 Vertex = {};
                        fscanf(File, "%f %f %f", &Vertex.X, &Vertex.Y, &Vertex.Z);
                        TempVertices[LastTempVertIndex++] = Vertex;
                    }
                    else if(strcmp(Line, VERTEX_TEXTURE_COORDINATE) == 0)
                    {
                        V2 Vertex= {};
                        fscanf(File, "%f %f", &Vertex.X, &Vertex.Y);
                        TempUVs[LastTempUVsIndex++] = Vertex;
                    }
                    else if(strcmp(Line, VERTEX_NORMAL) == 0)
                    {
                        V3 Vertex = {};
                        fscanf(File, "%f %f %f", &Vertex.X, &Vertex.Y, &Vertex.Z);
                        TempNormals[LastTempNormalsIndex++] = Vertex;
                    }
                    else if(strcmp(Line, VERTEX_FACE) == 0)
                    {   
                        int Matches = fscanf(File, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
                                             &TempVerticeIndices[LastTempVertIndiceIndex++], &TempUVsIndices[LastTempUVsIndiceIndex++], &TempNormalsIndices[LastTempNormalsIndiceIndex++],
                                             &TempVerticeIndices[LastTempVertIndiceIndex++], &TempUVsIndices[LastTempUVsIndiceIndex++], &TempNormalsIndices[LastTempNormalsIndiceIndex++],
                                             &TempVerticeIndices[LastTempVertIndiceIndex++], &TempUVsIndices[LastTempUVsIndiceIndex++], &TempNormalsIndices[LastTempNormalsIndiceIndex++],
                                             &TempVerticeIndices[LastTempVertIndiceIndex++], &TempUVsIndices[LastTempUVsIndiceIndex++], &TempNormalsIndices[LastTempNormalsIndiceIndex++]);
                        
                        if(Matches != FACE_MATCH_COUNT)
                        {
                            SDL_Log("Incorrect number of faces in Obj %s", FilePath);
                            fclose(File);
                            
                            loaded_obj FailedResult = {};
                            return FailedResult;
                        }
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
        Result.Vertices.Vertex = (V3*)PlatformAlloc(sizeof(V3) * LastTempVertIndex);
        Result.Vertices.Vertex = TempVertices;
        Result.Vertices.VertexCount = LastTempVertIndex;
        
        Result.UVs.UVVertex = (V2*)PlatformAlloc(sizeof(V2) * LastTempUVsIndex);
        Result.UVs.UVVertex = TempUVs;
        Result.UVs.VertexCount = LastTempUVsIndex;
        
        Result.Normals.Vertex = (V3*)PlatformAlloc(sizeof(V3) * LastTempNormalsIndex);
        Result.Normals.Vertex = TempNormals;
        Result.Normals.VertexCount = LastTempNormalsIndex;
                
        // Indices
        Result.Vertices.Indice = (unsigned int*)PlatformAlloc(sizeof(int) * LastTempVertIndiceIndex);
        Result.Vertices.Indice = TempVerticeIndices;
        Result.Vertices.IndiceCount = LastTempVertIndiceIndex;
        
        Result.UVs.Indice = (unsigned int*)PlatformAlloc(sizeof(int) * LastTempUVsIndiceIndex);
        Result.UVs.Indice = TempUVsIndices;
        Result.UVs.IndiceCount = LastTempUVsIndiceIndex;
        
        Result.Normals.Indice = (unsigned int*)PlatformAlloc(sizeof(int) * LastTempNormalsIndiceIndex);
        Result.Normals.Indice = TempNormalsIndices;
        Result.Normals.IndiceCount = LastTempNormalsIndiceIndex;
        
        fclose(File);
        return Result;
    }
};