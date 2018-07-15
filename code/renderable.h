#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "shader.h"
#include "image.h"

namespace renderable
{
    
#define RENDERABLE(BufferSize) static const int BUFFER_SIZE = BufferSize * sizeof(renderable_info); \
    static bool Init(const char* MeshFilePath); \
    static void InitBuffer(); \
    static void DeleteBuffer(); \
    static void Make(const char* TextureFilePath, const char* MeshFilePath, bool bOrtho); \
    static void Make(const char* TextureFilePath, const char* MeshFilePath, const transforms::transform Transform, bool bOrtho); \
    static renderable_info MakeAndReturn(const char* TextureFilePath, const transforms::transform Transform, bool bOrtho); \
    static void Update(); \
    static unsigned int LastAvailableID = 0; \
    static renderable_info* Buffer = nullptr; \
    static renderable_info Single = {};
    
    enum RENDERABLE_TYPE
    {
        NONE,
        ARRAYS,
        ELEMENTS,
        
        MAX
    };
    
    struct renderable_info
    {        
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        unsigned int ID;
        unsigned int IndiceCount;
        RENDERABLE_TYPE Type;
        bool bOrtho;

        transforms::transform Transform;
        image::image_info TextureInfo;        
        shader::shader_info ShaderInfo;
    };
    
    static renderable_info Make(const char* TextureFilePath, const int VerticesSize, const float Vertices[], const int IndiceSize, const int Indices[], bool bOrtho);    
    static renderable_info Make(const char* TextureFilePath, const int VerticesSize, const float Vertices[], bool bOrtho);
    static renderable_info Make(const char* TextureFilePath, const int VerticesSize, const V3 Vertices[], bool bOrtho);
    static void Update(renderable_info Info);
};

#endif