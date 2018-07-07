#include "math.h"

#include <math.h>

namespace math
{
    V3 MakeV3(const float X, const float Y, const float Z)
    {
        V3 Result = {};
        Result.X = X;
        Result.Y = Y;
        Result.Z = Z;
        return Result;
    }
    
    M4 Perspective(const float FOV, const float AspectRatio, const float NearPlane, const float FarPlane)
    {
        M4 Result = IDENTITY_MATRIX;
        
        float TanThetaOver2 = HMM_TanF(FOV * (PI / 360.0f));
        
        Result.M[0][0] = 1.0f / TanThetaOver2;
        Result.M[1][1] = AspectRatio / TanThetaOver2;
        Result.M[2][3] = -1.0f;
        Result.M[2][2] = (NearPlane + FarPlane) / (NearPlane - FarPlane);
        Result.M[3][2] = (2.0f * NearPlane * FarPlane) / (NearPlane - FarPlane);
        Result.M[3][3] = 0.0f;
        
        return Result;        
    }
    
    M4 Orthographic(const float Left, const float Right, const float Bottom, const float Top, const float Near, const float Far)
    {
        M4 Result = IDENTITY_MATRIX;
        
        Result.M[0][0] = 2.0f / (Right - Left);
        Result.M[1][1] = 2.0f / (Top - Bottom);
        Result.M[2][2] = 2.0f / (Near - Far);
        Result.M[3][3] = 1.0f;
        
        Result.M[3][0] = (Left + Right) / (Left - Right);
        Result.M[3][1] = (Bottom + Top) / (Bottom - Top);
        Result.M[3][2] = (Far + Near) / (Near - Far);
        
        return Result;
    }
    
    M4 LookAt(const V3 Location, const V3 LookingAt, const V3 Up)
    {        
        M4 Result = IDENTITY_MATRIX;
        
        V3 F = Normalize(Subtract(LookingAt, Location));
        V3 S = Normalize(Cross(F, Up));
        V3 U = Cross(S, F);
        
        Result.M[0][0] =  S.X;
        Result.M[0][1] =  U.X;
        Result.M[0][2] = -F.X;
        Result.M[0][3] =  0.0f;
        
        Result.M[1][0] =  S.Y;
        Result.M[1][1] =  U.Y;
        Result.M[1][2] = -F.Y;
        Result.M[1][3] =  0.0f;
        
        Result.M[2][0] =  S.Z;
        Result.M[2][1] =  U.Z;
        Result.M[2][2] = -F.Z;
        Result.M[2][3] =  0.0f;
        
        Result.M[3][0] = -Dot(S, Location);
        Result.M[3][1] = -Dot(U, Location);
        Result.M[3][2] =  Dot(F, Location);
        Result.M[3][3] =  1.0f;
        
        return Result;
    }
    
    V3 Subtract(const V3 Left, const V3 Right)
    {
        V3 Result = {};
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;
        Result.Z = Left.Z - Right.Z;
        return Result;
    }
    
    V3 Multiply(const V3 Left, const V3 Right)
    {
        V3 Result = {};
        
        Result.X = Left.X * Right.X;
        Result.Y = Left.Y * Right.Y;
        Result.Z = Left.Z * Result.Z;
        return Result;
    }
    
    V3 Cross(const V3 Left, const V3 Right)
    {
        V3 Result = {};
        Result.Elements[0] = Left.Elements[1] * Right.Elements[2] - Left.Elements[2] * Right.Elements[1];
        Result.Elements[1] = Left.Elements[2] * Right.Elements[0] - Left.Elements[0] * Right.Elements[2];
        Result.Elements[2] = Left.Elements[0] * Right.Elements[1] - Left.Elements[1] * Right.Elements[0];
        return Result;
    }
    
    float Radians(const float Degrees)
    {
        float Result = Degrees * (PI / 180.0f);        
        return Result;
    }
    
    float Dot(const V3 Left, const V3 Right)
    {
        return Left.Elements[0] * Right.Elements[0] + Left.Elements[1] * Right.Elements[1] + Left.Elements[2] * Right.Elements[2];
    }
     
    float LengthSquared(const V3 Left)
    {
        return Dot(Left, Left);
    }
    
    float Length(const V3 Left)
    {
        return sqrt(LengthSquared(Left));
    }
    
    V3 Normalize(const V3 Left)
    {        
        V3 Result = {};
        float VectorLength = Length(Left);
        
        if (VectorLength != 0.0f)
        {
            Result.X = Left.X * (1.0f / VectorLength);
            Result.Y = Left.Y * (1.0f / VectorLength);
            Result.Z = Left.Z * (1.0f / VectorLength);
        }        
        return Result;
    }
    
    M4 MultiplyM4(const M4 Left, const M4 Right)
    {        
        M4 Result = IDENTITY_MATRIX;
        
        int Columns;
        for(Columns = 0; Columns < 4; ++Columns)
        {
            int Rows;
            for(Rows = 0; Rows < 4; ++Rows)
            {
                float Sum = 0;
                int CurrentMatrice;
                for(CurrentMatrice = 0; CurrentMatrice < 4; ++CurrentMatrice)
                {
                    Sum += Left.M[CurrentMatrice][Rows] * Right.M[Columns][CurrentMatrice];
                }
                
                Result.M[Columns][Rows] = Sum;
            }
        }
        
        return Result;
    }
    
    M4 Translate(V3 Translation)
    {
        M4 Result = IDENTITY_MATRIX;
        
        Result.M[3][0] = Translation.X;
        Result.M[3][1] = Translation.Y;
        Result.M[3][2] = Translation.Z;
        
        return (Result);
    }
    
    void Scale(M4* Matrix, const V3 Left)
    {   
        Matrix->M[0][0] = Left.X;
        Matrix->M[1][1] = Left.Y;
        Matrix->M[2][2] = Left.Z;
    }
    
    M4 Scale(const V3 Left)
    {
        M4 Result = IDENTITY_MATRIX;
        
        Result.M[0][0] = Left.X;
        Result.M[1][1] = Left.Y;
        Result.M[2][2] = Left.Z;
        
        return Result;   
    }
};