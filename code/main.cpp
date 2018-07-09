#include "includes.h"

int main(int argc, char* argv[])
{   
    display::Make();
    
    V3 cubePositions[] = {
        MakeV3( 0.0f,  0.0f,  0.0f), 
        MakeV3( 2.0f,  5.0f, -15.0f), 
        MakeV3(-1.5f, -2.2f, -2.5f),  
        MakeV3(-3.8f, -2.0f, -12.3f),  
        MakeV3( 2.4f, -0.4f, -3.5f),  
        MakeV3(-1.7f,  3.0f, -7.5f),  
        MakeV3( 1.3f, -2.0f, -200.5f),  
        MakeV3( 1.5f,  2.0f, -2.5f), 
        MakeV3( 1.5f,  0.2f, -1.5f), 
        MakeV3(-1.3f,  1.0f, -1.5f)  
    };
    
    for(int i = 0; i < 10; ++i)
    {        
        cube::Make("../content/default_grid.tga", transforms::MakeFromVector(cubePositions[i]), false); 
    }
    
    transform QuadTransform = transforms::Make(MakeV3(0.f, 0.95f, 0.f), MakeV3(0.f, 0.f, 0.f), MakeV3(1.f, 0.05f, 1.f));
    quad::Make("../content/orange.tga", QuadTransform, true);
    while(display::Update())
    {
        timing::Begin();
        
        glClearColor(0.f, 0.1f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        cube::Update();
        quad::Update();
        
        timing::End();
        
        SDL_GL_SwapWindow(display::Window);
    }
    
    cube::DeleteBuffer();
    quad::DeleteBuffer();
    
    SDL_Quit();
    return 0;
}