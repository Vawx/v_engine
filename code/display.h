#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define ASPECT_RATIO ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)

namespace display
{
    enum SwapInterval
    {
        IMMEDIATE = 0,
        VSYNC = 1,
    };
    
    SDL_Window* Window;
    SDL_GLContext Context;
    
    static int CurrentWindowWidth;
    static int CurrentWindowHeight;
    
    static V2 WindowSize;
    
    static void Make();
    static bool Update();
    static void UpdateWindowSize(const int Width, const int Height);
    static V2 GetWindowSize();
};

#endif