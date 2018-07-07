#include "timing.h"

#include "sdl/sdl.h"

namespace timing
{   
    void Begin()
    {
        StartTicks = SDL_GetTicks();    
    }
    
    void End()
    {
        CalculateFPS();
        
        float FrameTicks = SDL_GetTicks( ) - StartTicks;
        if( 1000.f / TARGET_FPS >= FrameTicks)
        {
            SDL_Delay(int(1000.f / TARGET_FPS - FrameTicks));
        }
        EndFrameTime = SDL_GetTicks( );
        DeltaTime = (EndFrameTime - StartTicks) * 0.001f;
    }
    
    void CalculateFPS()
    {
        static const int NUM_SAMPLES = 10;
        static float FrameTimes[ NUM_SAMPLES ];
        static int CurrentFrame = 0;
        static float PreviousTicks = SDL_GetTicks( );
        float CurrentTicks = SDL_GetTicks( );
        
        StartFrameTime = CurrentTicks - PreviousTicks;
        FrameTimes[CurrentFrame % NUM_SAMPLES] = StartFrameTime;
        PreviousTicks = CurrentTicks;
        
        CurrentFrame++;
        int Count = (CurrentFrame < NUM_SAMPLES) ? CurrentFrame : NUM_SAMPLES;
        
        float FrameTimeAverage = 0;
        for(int i = 0; i < Count; ++i)
        {
            FrameTimeAverage += FrameTimes[i];
        }
        FrameTimeAverage /= Count;
        FPS = (FrameTimeAverage > 0 ) ? 1000.f / FrameTimeAverage : TARGET_FPS;
        
    }
};