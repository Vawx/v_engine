#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "shader.h"
#include "image.h"

namespace renderable
{
    
#define RENDERABLE(BufferSize) static const int BUFFER_SIZE = BufferSize * sizeof(renderable_info); \
    static void InitBuffer(); \
    static void DeleteBuffer(); \
    static void Make(const char* TextureFilePath, bool bOrtho); \
    static void Make(const char* TextureFilePath, const transforms::transform Transform, bool bOrtho); \
    static void Update(); \
    static unsigned int LastAvailableID = 0; \
    static renderable_info* Buffer = nullptr; 
    
    struct renderable_info
    {        
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        unsigned int ID;
        bool bOrtho;

        transforms::transform Transform;
        image::image_info TextureInfo;        
        shader::shader_info ShaderInfo;
    };
    
    static renderable_info Make(const char* TextureFilePath, const int VerticesSize, const float Vertices[], const int IndiceSize, const unsigned int Indices[], bool bOrtho);
    static renderable_info Make(const char* TextureFilePath, const int VerticesSize, const float Vertices[], bool bOrtho);
    static bool bValid(const renderable_info Info);    
};

#endif