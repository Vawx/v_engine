#include "transform.h"

namespace transforms
{   
    transform MakeFromVector(const V3 Location)
    {
        transform Result = Empty();
        Result.Location = Location;
        return Result;
    }
    
    transform Make(const V3 Location, const V3 Rotation, const V3 Scale)
    {
        transform Result = {};
        Result.Location = Location;
        Result.Rotation = Rotation;
        Result.Scale = Scale;
        return Result;
    }
    
    transform Empty()
    {
        transform Result = {};
        Result.Location = MakeV3(0.f, 0.f, 0.f);
        Result.Rotation = MakeV3(0.f, 0.f, 0.f);
        Result.Scale = MakeV3(1.f, 1.f, 1.f);
        Result.Direction = 0.f;
        
        return Result;
    }
};