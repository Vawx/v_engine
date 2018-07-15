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
    
    #define TEMP_BUFFER_SIZE 20000        
    #define TRIANGLE_FACE_MATCH_COUNT 9
    
    enum object_faces
    {
        NONE,
        QUAD,
        TRIANGLE,
    };
    
    struct vertex_indice_data
    {
        V3* Vertex;
        int* Indice;
        
        int IndiceCount;
        int VertexSize;
    };
    
    struct loaded_obj
    {
        char* ObjectName;
        object_faces FaceType;
        
        vertex_indice_data Vertices;
        vertex_indice_data UVs;
        vertex_indice_data Normals;
    };
        
    static loaded_obj LoadObj(const char* FilePath);  
};

#endif