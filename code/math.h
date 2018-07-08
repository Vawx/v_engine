#ifndef _MATH_H_
#define _MATH_H_

#define HANDMADE_MATH_IMPLEMENTATION
#include "math/handmade_math.h"

namespace math
{   
    #define PI 3.14159265359
    
    struct M4
    {
        float M[4][4];
    };
    
    static const M4 IDENTITY_MATRIX = 
    {{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    }};
    
    union V3
    {
        float Elements[3];
        struct 
        {
            float X, Y, Z;  
        };
                
        struct
        {
            float Pitch, Yaw, Roll;  
        };
        
        struct
        {
            float R, G, B;
        };
    };
    
    union V2
    {
        float Elements[2];
        struct
        {
            float X, Y;
        };
        
        struct
        {
            float Min, Max;
        };
        
        struct 
        {
            float Width, Height;  
        };
    };
    
    static V3 MakeV3(const float X, const float Y, const float Z);    
    static V2 MakeV2(const float X, const float Y);
    static M4 Perspective(const float FOV, const float AspectRatio, const float NearPlane, const float FarPlane);
    static M4 Orthographic(const float Left, const float Right, const float Bottom, const float Top, const float Near, const float Far);
    static V3 Cross(const V3 Left, const V3 Right);
    static float Dot(const V3 Left, const V3 Right);
    static V3 Normalize(const V3 Left);
    static M4 MultiplyM4(const M4 Left, const M4 Right);
    static M4 Translate(const V3 Translation);
    static M4 LookAt(const V3 Location, const V3 LookingAt, const V3 Up); 
    static M4 Scale(const V3 Left);    
    static void Scale(M4* Matrix, const V3 Left);
    static V3 Subtract(const V3 Left, const V3 Right);
    static V3 Multiply(const V3 Left, const V3 Right);
    static float LengthSquared(const V3 Left);
    static float Length(const V3 Left);
    static float Radians(const float Degrees);
    
    V3 operator+(V3 Left, const V3& Right)
    {
        V3 Result = {};
        Result.X = Left.X + Right.X;
        Result.Y = Left.Y + Right.Y;
        Result.Z = Left.Z + Right.Z;
        return Result;
    }
    
    V3 operator-(V3 Left, const V3& Right)
    {
        V3 Result = {};
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;
        Result.Z = Left.Z - Right.Z;
        return Result;
    }
    
    V3 &operator+=(V3& Left, const V3& Right)
    {
        return (Left = Left + Right);
    }
    
    V3 &operator-=(V3& Left, const V3& Right)
    {
        return (Left = Left - Right);
    }
    
    V3 operator*(V3 Left, const float& Right)
    {        
        V3 Result = {};
        Result.X = Left.X * Right;
        Result.Y = Left.Y * Right;
        Result.Z = Left.Z * Right;
        return Result;    
    }
    
    V3 operator*=(V3 Left, const V3& Right)
    {
        V3 Result = Left;
        Result.X *= Right.X;
        Result.Y *= Right.Y;
        Result.Z *= Result.Z;
        return Result;
    }
     
    #define V3_FRONT MakeV3(0.f, 0.f, 1.f)
    #define V3_RIGHT MakeV3(1.f, 0.f, 0.f)
    #define V3_UP MakeV3(0.f, -1.f, 0.f)
};

#endif