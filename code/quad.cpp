#include "quad.h"

namespace quad
{
    void InitBuffer()
    {
        if(Buffer == nullptr)
        {
            // Buffer memory
           Buffer = (renderable_info*)malloc(BUFFER_SIZE);
            
            // Clear memory with empty structs as malloc doesnt do that default.
            renderable_info Empty = {};
            for(int BufferIndex = 0; BufferIndex < BUFFER_SIZE / sizeof(renderable_info); ++BufferIndex)
            {
                Buffer[BufferIndex] = Empty;
            }
        }
    }
        
    void DeleteBuffer()
    {
        if(Buffer)
        {
            free(Buffer);
        }
    }
        
    void Make(const char* TextureFilePath, bool bOrtho)
    {
        // Check for buffer memory before trying to add
        InitBuffer();
        
        // Have available space
        if(LastAvailableID < BUFFER_SIZE)
        {
            // Create quad
            renderable_info Result = renderable::Make(TextureFilePath, sizeof(Vertices), Vertices, sizeof(Indices), Indices, bOrtho);
            
            // Attribs for aPos and aTexCoord layout in shader (0), (1)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);    
            
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            
            // Keep track of ID
            Result.ID = LastAvailableID;
            Buffer[LastAvailableID++] = Result;
        }
    }
    
    void Make(const char* TextureFilePath, const transforms::transform Transform, bool bOrtho)
    {        
        // Check for buffer memory before trying to add
        InitBuffer();
        
        // Have available space
        if(LastAvailableID < BUFFER_SIZE)
        {
            // Create quad
            renderable_info Result = renderable::Make(TextureFilePath, sizeof(Vertices), Vertices, sizeof(Indices), Indices, bOrtho);
            
            // Attribs for aPos and aTexCoord layout in shader (0), (1)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);    
            
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            
            Result.Transform = Transform;
            
            // Keep track of ID
            Result.ID = LastAvailableID;
            Buffer[LastAvailableID++] = Result;
        }
    }
    
    void Update()
    {
        // Check buffer for valid
        if(Buffer)
        {
            // Loop up to LastAvailableID
            for(int BufferIndex = 0; BufferIndex < LastAvailableID; ++BufferIndex)
            {                   
                glEnable(GL_DEPTH_TEST);                  
                glUseProgram(Buffer[BufferIndex].ShaderInfo.ShaderID);
                
                if(Buffer[BufferIndex].bOrtho)
                {
                    glDisable(GL_DEPTH_TEST);  
                }
                else
                {                    
                    // Camera
                    camera::TransformCamera(Buffer[BufferIndex].ShaderInfo.ShaderID, Buffer[BufferIndex].bOrtho);                                    
                }
                
                // Transform
                unsigned int TransformLocation = glGetUniformLocation(Buffer[BufferIndex].ShaderInfo.ShaderID, "transform");                
                M4 TransformMatrix = Translate(Buffer[BufferIndex].Transform.Location);
                Scale(&TransformMatrix, Buffer[BufferIndex].Transform.Scale);                
                glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, TransformMatrix.M[0]);  
                
                // Render
                glBindTexture(GL_TEXTURE_2D, Buffer[BufferIndex].TextureInfo.TextureID);
                glBindVertexArray(Buffer[BufferIndex].VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);      
            }
        }        
    }    
};