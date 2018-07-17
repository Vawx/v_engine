#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}
#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define WINDOWS
#include "windows.h"
#endif

#include "sdl/sdl.h"
#include "gl/glew.h"
#include "sdl/sdl_opengl.h"

#if defined(WINDOWS)
#define PlatformAlloc(Size) \
VirtualAlloc(0, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
#define PlatformAlloc(Size) \
malloc(size);
SDL_Log("Using Malloc!");
#endif

#include "math.cpp"
#include "transform.cpp"

#include "timing.cpp"

#include "input.cpp"
#include "camera.cpp"
#include "display.cpp"

#include "loadobj.cpp"
#include "mesh.cpp"

#include "ui.cpp"

#endif