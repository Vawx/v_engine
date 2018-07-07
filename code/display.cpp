#include "display.h"

namespace display
{
    void Make()
    {        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
        if(Window)
        {
            Context = SDL_GL_CreateContext(Window);
            if(Context)
            {                
                glewExperimental = GL_TRUE;
                GLenum Error = glewInit();
                if(Error == GLEW_OK)
                {
                    SDL_GL_SetSwapInterval(SwapInterval::VSYNC);
                    camera::Init(ASPECT_RATIO);                    
                }
            }
        }
    }
    
    bool Update()
    {
        bool bQuit = input::Process();
        if(bQuit)
        {
            if(input::KeyPressed(SDLK_ESCAPE))
            {
                bQuit = false;
            }
        }
        
        camera::Update();
        return bQuit;
    }
};