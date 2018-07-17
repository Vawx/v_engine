#include "camera.h"

using namespace input;
namespace camera
{
    static void Init(const float AspectRatio)
    {
        Transform = transforms::Empty();
        Transform.Location = MakeV3(0.f, 0.f, 0.f);
        Transform.Rotation = MakeV3(0.f, 0.f, 0.f);
            
        Projection = Perspective(DEFAULT_FOV, AspectRatio, CLIP_PLANE_SHORT, CLIP_PLANE_LONG);
        Ortho = Orthographic(0.f, WINDOW_WIDTH, 0.f, WINDOW_HEIGHT, CLIP_PLANE_SHORT, CLIP_PLANE_LONG);
        RotateCamera(0.f, 0.f);
    }
    
    static void ReInit(const int Width, const int Height)
    {   
        const float NewAspectRation = ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);
        Projection = Perspective(DEFAULT_FOV, NewAspectRation, CLIP_PLANE_SHORT, CLIP_PLANE_LONG);
        Ortho = Orthographic(0.f, Width, 0.f, Height, CLIP_PLANE_SHORT, CLIP_PLANE_LONG);
    }
    
    static void RotateCamera(const float XOffset, const float YOffset)
    {
        Transform.Rotation.X += XOffset;
        Transform.Rotation.Y += YOffset;
        
        V3 Rotation = MakeV3(0.f, 0.f, 0.f);
        Rotation.X = cos(Radians(Transform.Rotation.X)) * cos(Radians(Transform.Rotation.Y));
        Rotation.Y = sin(Radians(Transform.Rotation.Y));
        Rotation.Z = sin(Radians(Transform.Rotation.X)) * cos(Radians(Transform.Rotation.Y));
        CameraDirection = Normalize(Rotation);        
    }
        
    void Update()
    {
        // Add mouse input for left click, right click, both click
        // Left click: forward/backward movement along direction
        // Right click: stationary look around 
        // Both click: Y plane movement (up,down,left,right)
        // Space bar: Camera up
        // Mouse Wheel: zoom in out
        
        static int LastMouseY = 0;
        static int LastMouseX = 0;
        
        int CurrentMouseY = MouseY;
        int CurrentMouseX = MouseX;
        
        if(KeyPressed(SDLK_w))
        {
            Transform.Location += CameraDirection * MOVE_SPEED_SET(timing::DeltaTime, MOVE_SLOW);
        }
        if(KeyPressed(SDLK_s))
        {
            Transform.Location -= CameraDirection * MOVE_SPEED_SET(timing::DeltaTime, MOVE_SLOW);
        }
                
        V3 Crossed = Cross(CameraDirection, V3_UP);
        if(KeyPressed(SDLK_d))
        {
            Transform.Location += Normalize(Crossed) * MOVE_SPEED_SET(timing::DeltaTime, MOVE_SLOW);
        }
        if(KeyPressed(SDLK_a))
        {
            Transform.Location -= Normalize(Crossed) * MOVE_SPEED_SET(timing::DeltaTime, MOVE_SLOW);
        }
        
        if(KeyPressed(SDLK_SPACE))
        {
            Transform.Location.Y -= MOVE_SPEED_SET(timing::DeltaTime, MOVE_SLOW);
        }
        
        if(ButtonPressed(SDL_BUTTON_RIGHT) && ButtonPressed(SDL_BUTTON_LEFT))
        {         
            const V3 Right = Cross(CameraDirection, V3_UP);
            if(LastMouseY != 0)
            {
                if(CurrentMouseY != LastMouseY)
                {   
                    float DifferenceY = 0.f;
                    if(CurrentMouseY > LastMouseY)
                    {
                        DifferenceY = (CurrentMouseY - LastMouseY) * timing::DeltaTime;
                        Transform.Location += V3_UP * DifferenceY;
                    }
                    else
                    {
                        DifferenceY = (LastMouseY - CurrentMouseY) * timing::DeltaTime;
                        Transform.Location -= V3_UP * DifferenceY;                        
                    }
                }
            }
            if(LastMouseX != 0)
            {
                if(CurrentMouseX != LastMouseX)
                {
                    float DifferenceX = 0.f;
                    if(CurrentMouseX > LastMouseX)
                    {
                        DifferenceX = (CurrentMouseX - LastMouseX) * timing::DeltaTime;
                        Transform.Location -= Right * DifferenceX;
                    }
                    else
                    {
                        DifferenceX = (LastMouseX - CurrentMouseX) * timing::DeltaTime;
                        Transform.Location += Right * DifferenceX;                        
                    }
                }
             }
        }
        else if(ButtonPressed(SDL_BUTTON_RIGHT))
        {               
            const float DifferenceX = (LastMouseX - CurrentMouseX) * MOVE_SPEED_SET(timing::DeltaTime, MOVE_SLOW);
            const float DifferenceY = (CurrentMouseY - LastMouseY) * MOVE_SPEED_SET(timing::DeltaTime, MOVE_SLOW);
            
            if(DifferenceX != 0.f || DifferenceY != 0.f)
            {
                RotateCamera(DifferenceX, DifferenceY);
            }
        }
        else if(ButtonPressed(SDL_BUTTON_LEFT))
        {
            if(CurrentMouseY > LastMouseY)
            {                
                Transform.Location -= CameraDirection * MOVE_SPEED_SET(timing::DeltaTime, MOVE_FAST);
            }
            else if(CurrentMouseY < LastMouseY)
            {                
                Transform.Location += CameraDirection * MOVE_SPEED_SET(timing::DeltaTime, MOVE_FAST);
            }
        }
        
        if(WheelDirection == MOUSE_WHEEL_DIRECTION::UP)
        {           
            Transform.Location += CameraDirection * MOVE_SPEED_SET(timing::DeltaTime, MOVE_REAL_FAST);
        }
        else if(WheelDirection == MOUSE_WHEEL_DIRECTION::DOWN)
        {            
            Transform.Location -= CameraDirection * MOVE_SPEED_SET(timing::DeltaTime, MOVE_REAL_FAST);
        }
        
        LastMouseY = CurrentMouseY;
        LastMouseX = CurrentMouseX;
        
        View = LookAt(Transform.Location, Transform.Location + CameraDirection, V3_UP);        
    }
    
    
    void TransformCamera(const GLuint ShaderID)
    {           
        unsigned int ViewID = glGetUniformLocation(ShaderID, VIEW);
        glUniformMatrix4fv(ViewID, 1, GL_FALSE, View.M[0]);  
        
        unsigned int ProjectionID = glGetUniformLocation(ShaderID, PROJECTION);
        glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, Projection.M[0]);
    }
};