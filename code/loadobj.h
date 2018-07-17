#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

/*
Simple Wavefront Obj parsing.

v is a vertex
vt is the texture coordinate of one vertex
vn is the normal of one vertex
f is a face
g is object name
*/

namespace load_obj
{
    #define VERTEX "v"
    #define VERTEX_TEXTURE_COORDINATE "vt"
    #define VERTEX_NORMAL "vn"
    #define VERTEX_FACE "f"
    #define OBJECT_NAME "g"
    
    #define TEMP_BUFFER_SIZE 65536        
    #define TRIANGLE_FACE_MATCH_COUNT 9
    
    struct vertex_indice_data
    {
        V3* Vertex;
        int* Indice;
        
        union
        {
            V2* UVVertex;
        };
        
        int IndiceCount;
        int VertexSize;
    };
    
    struct object_data
    {
        V3* Vertex;
        V2* UV;
        V3* Normal;
        
        iV2 VertexSizeCount;
        iV2 UVSizeCount;
        iV2 NormalSizeCount;
    };
    
    struct face_data
    {
        unsigned int Vertex;
        unsigned int UV;
        unsigned int Normal;
    };
    
    struct loaded_obj
    {
        char* ObjectName;
        
        object_data Data;        
    };
        
    static loaded_obj LoadObj(const char* FilePath);  
};

#endif