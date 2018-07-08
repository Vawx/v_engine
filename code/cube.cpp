#include "cube.h"

#include "renderable.cpp"

namespace cube
{
    void InitBuffer()
    {
        if(Buffer == nullptr)
        {
            Buffer = (renderable_info*)malloc(BUFFER_SIZE);
            
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
    
    void Make(const char* TextureFilePath, const transforms::transform Transform, bool bOrtho)
    {        
        InitBuffer();
        
        // Have available space
        if(LastAvailableID < BUFFER_SIZE)
        {
            // Create quad
            renderable_info Result = renderable::Make(TextureFilePath, sizeof(Vertices), Vertices, bOrtho);
            
            // Attribs for aPos and aTexCoord layout in shader (0), (1)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);    
            
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            
            Result.Transform = Transform;
            
            Result.Type = RENDERABLE_TYPE::ARRAYS;
            
            // Keep track of ID
            Result.ID = LastAvailableID;
            Buffer[LastAvailableID++] = Result;            
        }
    }
    
    void Make(const char* TextureFilePath, bool bOrtho)
    {
        InitBuffer();
        
        // Have available space
        if(LastAvailableID < BUFFER_SIZE)
        {
            // Create quad
            renderable_info Result = renderable::Make(TextureFilePath, sizeof(Vertices), Vertices, bOrtho);
            
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
    
    void Update()
    {
        // Check buffer for valid
        if(Buffer)
        {
            // Loop up to LastAvailableID
            for(int BufferIndex = 0; BufferIndex < LastAvailableID; ++BufferIndex)
            {                   
                renderable::Update(Buffer[BufferIndex]);
            }
        }        
    }    
};