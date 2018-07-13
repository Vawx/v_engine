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
        
        Result.EBO = 0;
        return Result;
    }
    
    void Update(renderable_info Info)
    {        
        glEnable(GL_DEPTH_TEST);                  
        glUseProgram(Info.ShaderInfo.ShaderID);
        
        if(Info.bOrtho)
        {
            glDisable(GL_DEPTH_TEST);  
        }
        else
        {                    
            // Camera
            camera::TransformCamera(Info.ShaderInfo.ShaderID);                                    
        }
        
        // Transform
        unsigned int TransformLocation = glGetUniformLocation(Info.ShaderInfo.ShaderID, "transform");                
        M4 TransformMatrix = Translate(Info.Transform.Location);
        Scale(&TransformMatrix, Info.Transform.Scale);                
        glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, TransformMatrix.M[0]);  
        
        // Render
        glBindTexture(GL_TEXTURE_2D, Info.TextureInfo.TextureID);
        glBindVertexArray(Info.VAO);
        
        if(Info.Type == RENDERABLE_TYPE::ELEMENTS)
        {
            glDrawElements(GL_TRIANGLES, Info.IndiceCount, GL_UNSIGNED_INT, 0);
        }
        else if(Info.Type == RENDERABLE_TYPE::ARRAYS)
        {
            glDrawArrays(GL_TRIANGLES, 0, Info.IndiceCount);
        }
        
        glBindVertexArray(0);      
    }
};