#include "mesh.h"

namespace mesh
{
    bool Init(const char* MeshFilePath)
    {        
        Object = load_obj::LoadObj(MeshFilePath);
        return true;
    }
    
    void Make(const char* TextureFilePath, const char* MeshFilePath, const transforms::transform Transform, bool bOrtho)
    {
        if(Init(MeshFilePath))
        {
            const int VerticeSize = Object.Vertices.VertexSize;
            const int IndiceSize = Object.Vertices.IndiceCount;
            
            Single = renderable::Make(TextureFilePath, VerticeSize, Object.Vertices.Vertex, bOrtho);
            Single.Type = RENDERABLE_TYPE::ARRAYS;
  
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(0);
              
            Single.Transform = Transform;
            Single.IndiceCount = Object.Vertices.IndiceCount;
        }
    }
    
    void Update()
    {
        renderable::Update(Single);
    }
};