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
            
            Result.Type = RENDERABLE_TYPE::ELEMENTS;    
            
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
            Result.IndiceCount = QUAD_INDICES;
            
            Result.Type = RENDERABLE_TYPE::ELEMENTS;
            // Keep track of ID
            Result.ID = LastAvailableID;
            Buffer[LastAvailableID++] = Result;
        }
    }
        
    renderable_info MakeAndReturn(const char* TextureFilePath, const transforms::transform Transform, bool bOrtho)
    {
        // Create quad
        renderable_info Result = renderable::Make(TextureFilePath, sizeof(Vertices), Vertices, sizeof(Indices), Indices, bOrtho);
        
        // Attribs for aPos and aTexCoord layout in shader (0), (1)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);    
        
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        Result.Type = RENDERABLE_TYPE::ELEMENTS;        
        Result.IndiceCount = QUAD_INDICES;
        
        Result.Transform = Transform;
        
        return Result;
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