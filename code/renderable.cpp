#include "renderable.h"

#include "shader.cpp"
#include "image.cpp"

namespace renderable
{   
    renderable_info Make(const char* TextureFilePath, const int VerticesSize, const V3 Vertices[], 
                         const int UVSize, const V2 UVs[], const int NormalSize, const V3 Normals[], bool bOrtho)
    {
        renderable_info Result = {};
        Result.ShaderInfo = shader::Make(bOrtho);
        Result.TextureInfo = image::Load(TextureFilePath);
        Result.Transform = transforms::Empty();
        
        glGenVertexArrays(1, &Result.VAO);
        glBindVertexArray(Result.VAO);
        
        glGenBuffers(1, &Result.VBO);
        glBindBuffer(GL_ARRAY_BUFFER, Result.VBO);        
        glBufferData(GL_ARRAY_BUFFER, VerticesSize, &Vertices[0], GL_STATIC_DRAW);
        
        glGenBuffers(1, &Result.UV);
        glBindBuffer(GL_ARRAY_BUFFER, Result.UV);        
        glBufferData(GL_ARRAY_BUFFER, UVSize, &UVs[0], GL_STATIC_DRAW);
        
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
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, Info.VBO);            
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, Info.UV);            
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        glDrawArrays(GL_TRIANGLES, 0, Info.IndiceCount);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        glBindVertexArray(0);      
    }
};