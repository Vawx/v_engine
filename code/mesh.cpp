#include "mesh.h"

#include "renderable.cpp"

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
            Single = renderable::Make(TextureFilePath, Object.Data.VertexSizeCount.Size, Object.Data.Vertex, 
                                      Object.Data.UVSizeCount.Size, Object.Data.UV, Object.Data.NormalSizeCount.Size, 
                                      Object.Data.Normal, bOrtho);
            
            Single.Transform = Transform;
            Single.IndiceCount = Object.Data.VertexSizeCount.Count;
        }
    }
    
    void Update()
    {
        renderable::Update(Single);
    }
};