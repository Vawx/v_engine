#include "display.h"

namespace display
{
    void Make()
    {        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                
        WindowSize = MakeV2(WINDOW_WIDTH, WINDOW_HEIGHT);
        Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSize.Width, WindowSize.Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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
    
    static void UpdateWindowSize(const int Width, const int Height)
    {
        WindowSize = MakeV2(Width, Height);            
        
        // Update gl with window size
        glViewport(0, 0, WindowSize.Width, WindowSize.Height);
    }
    
    V2 GetWindowSize()
    {
        return WindowSize;
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
                
        // Update camera if window is resized
        SDL_WindowEvent Event = GetPresentWindowEvent(SDL_WINDOWEVENT_SIZE_CHANGED);
        if(Event.event != 0)
        {   
            UpdateWindowSize(Event.data1, Event.data2);
            
            // Update camera with window size
            camera::ReInit(WindowSize.Width, WindowSize.Height);            
        }
        
        camera::Update();
        return bQuit;
    }
};