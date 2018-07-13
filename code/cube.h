#ifndef _CUBE_H_
#define _CUBE_H_

#include "renderable.h"
using namespace renderable;

namespace cube
{
    #define CUBE_INDICIES 36
    
    float Vertices[] = {
        -1.f, -1.f, -1.f,  0.0f, 0.0f,
         1.f, -1.f, -1.f,  1.0f, 0.0f,
         1.f,  1.f, -1.f,  1.0f, 1.0f,
         1.f,  1.f, -1.f,  1.0f, 1.0f,
        -1.f,  1.f, -1.f,  0.0f, 1.0f,
        -1.f, -1.f, -1.f,  0.0f, 0.0f,
        
        -1.f, -1.f,  1.f,  0.0f, 0.0f,
         1.f, -1.f,  1.f,  1.0f, 0.0f,
         1.f,  1.f,  1.f,  1.0f, 1.0f,
         1.f,  1.f,  1.f,  1.0f, 1.0f,
        -1.f,  1.f,  1.f,  0.0f, 1.0f,
        -1.f, -1.f,  1.f,  0.0f, 0.0f,
        
        -1.f,  1.f,  1.f,  1.0f, 0.0f,
        -1.f,  1.f, -1.f,  1.0f, 1.0f,
        -1.f, -1.f, -1.f,  0.0f, 1.0f,
        -1.f, -1.f, -1.f,  0.0f, 1.0f,
        -1.f, -1.f,  1.f,  0.0f, 0.0f,
        -1.f,  1.f,  1.f,  1.0f, 0.0f,
        
         1.f,  1.f,  1.f,  1.0f, 0.0f,
         1.f,  1.f, -1.f,  1.0f, 1.0f,
         1.f, -1.f, -1.f,  0.0f, 1.0f,
         1.f, -1.f, -1.f,  0.0f, 1.0f,
         1.f, -1.f,  1.f,  0.0f, 0.0f,
         1.f,  1.f,  1.f,  1.0f, 0.0f,
        
        -1.f, -1.f, -1.f,  0.0f, 1.0f,
         1.f, -1.f, -1.f,  1.0f, 1.0f,
         1.f, -1.f,  1.f,  1.0f, 0.0f,
         1.f, -1.f,  1.f,  1.0f, 0.0f,
        -1.f, -1.f,  1.f,  0.0f, 0.0f,
        -1.f, -1.f, -1.f,  0.0f, 1.0f,
        
        -1.f,  1.f, -1.f,  0.0f, 1.0f,
         1.f,  1.f, -1.f,  1.0f, 1.0f,
         1.f,  1.f,  1.f,  1.0f, 0.0f,
         1.f,  1.f,  1.f,  1.0f, 0.0f,
        -1.f,  1.f,  1.f,  0.0f, 0.0f,
        -1.f,  1.f, -1.f,  0.0f, 1.0f
    };
    
    RENDERABLE(1024)
};

#endif