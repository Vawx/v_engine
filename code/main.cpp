#include "includes.h"

int main(int argc, char* argv[])
{   
    display::Make();
    
    mesh::Make("../content/Shaman_Diffuse.TGA", "../content/cube.obj", transforms::MakeFromVector(MakeV3(0.f, 0.f, 0.f)), false);
    
    while(display::Update())
    {
        timing::Begin();
        
        glClearColor(0.f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        mesh::Update();
        
        timing::End();
        
        SDL_GL_SwapWindow(display::Window);
    }
    
    SDL_Quit();
    return 0;
}