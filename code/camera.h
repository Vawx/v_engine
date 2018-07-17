#ifndef _CAMERA_H_
#define _CAMERA_H_

using namespace math;
using namespace transforms;

namespace camera
{    
    #define WINDOW_WIDTH 1280
    #define WINDOW_HEIGHT 720
    #define DEFAULT_FOV 90.f
    
    #define CLIP_PLANE_SHORT 0.1f
    #define CLIP_PLANE_LONG 1024 * 128
    
    #define VIEW "view"
    #define PROJECTION "projection"
    
    #define MOVE_SLOW 10.f
    #define MOVE_MEDIUM 20.f
    #define MOVE_FAST 40.f
    #define MOVE_REAL_FAST 60.f
    #define MOVE_SPEED_SET(Delta, Amount) Delta * Amount
    
    transform Transform;
    V3 CameraDirection;
    static M4 Projection;
    static M4 Ortho;
    static M4 View;    
    
    static void Init();
    static void Update();
    static void TransformCamera(const GLuint ShaderID);
    
    static void RotateCamera(const float XOffset, const float YOffset);
};

#endif