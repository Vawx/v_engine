#ifndef _TIMING_H_
#define _TIMING_H_

namespace timing
{
    #define TARGET_FPS 60
    
    static void Begin();
    static void End();
    static void CalculateFPS();
    
    static float StartFrameTime;
    static float EndFrameTime;
    static int StartTicks;
    
    float FPS;
    float DeltaTime;
};

#endif