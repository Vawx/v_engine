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
    
    #define TEMP_BUFFER_SIZE 8096    
    
    // Supporting non trianglated quads
    #define FACE_MATCH_COUNT 12
    
    struct vertex_indice_data
    {
        V3* Vertex;
        unsigned int* Indice;
        
        union
        {
            V2* UVVertex;
        };
        
        unsigned int VertexCount;
        unsigned int IndiceCount;
    };
    
    struct loaded_obj
    {
        char* ObjectName;
        
        vertex_indice_data Vertices;
        vertex_indice_data UVs;
        vertex_indice_data Normals;
    };
        
    static loaded_obj LoadObj(const char* FilePath);  
};

#endif