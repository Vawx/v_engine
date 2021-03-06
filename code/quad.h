#ifndef _QUAD_H_
#define _QUAD_H_

#include "renderable.h"
using namespace renderable;

namespace quad
{   
    #define QUAD_INDICES 6
    
    static float Vertices[] = {
         1.f,  1.f, 0.0f, 1.f, 1.f,
         1.f, -1.f, 0.0f, 1.f, 0.f,
        -1.f, -1.f, 0.0f, 0.f, 0.f, 
        -1.f,  1.f, 0.0f, 0.f, 1.f
    }; 
    
    static int Indices[] = {  
        0, 1, 3,   
        1, 2, 3   
    };  
    
    RENDERABLE(1024)
};

#endif