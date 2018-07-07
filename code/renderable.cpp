#include "renderable.h"

#include "shader.cpp"
#include "image.cpp"

namespace renderable
{
    renderable_info Make(const char* TextureFilePath, const int VerticesSize, const float Vertices[], const int IndiceSize, const unsigned int Indices[], bool bOrtho)
    {
        renderable_info Result = {};
        Result.ShaderInfo = shader::Make(bOrtho);
        Result.TextureInfo = image::Load(TextureFilePath);
        Result.Transform = transforms::Empty();
        
        glGenVertexArrays(1, &Result.VAO);
        glGenBuffers(1, &Result.VBO);
        glGenBuffers(1, &Result.EBO);
        
        glBindVertexArray(Result.VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, Result.VBO);
        glBufferData(GL_ARRAY_BUFFER, VerticesSize, Vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Result.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiceSize, Indices, GL_STATIC_DRAW);        
        return Result;
    }

    renderable_info Make(const char* TextureFilePath, const int VerticesSize, const float Vertices[], bool bOrtho)
    {
        renderable_info Result = {};
        Result.ShaderInfo = shader::Make(bOrtho);
        Result.TextureInfo = image::Load(TextureFilePath);
        Result.Transform = transforms::Empty();
        
        glGenVertexArrays(1, &Result.VAO);
        glGenBuffers(1, &Result.VBO);
        
        glBindVertexArray(Result.VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, Result.VBO);
        glBufferData(GL_ARRAY_BUFFER, VerticesSize, Vertices, GL_STATIC_DRAW);
        
        Result.EBO = -1;
        return Result;
    }
    
    bool bValid(const renderable_info Info)  
    {     
        // Valid is VBO, VAO, EBO, ShaderProgramID GREATER THAN 0.
        // (Default cleared all to 0).
        return Info.VBO > 0 && Info.VAO > 0 && Info.EBO > 0 && Info.ShaderInfo.ShaderID > 0;
    }
};