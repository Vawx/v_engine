#ifndef _TRANSFORMS_H_
#define _TRANSFORMS_H_

using namespace math;

namespace transforms
{
    struct transform
    {
        V3 Location;
        V3 Scale;
        V3 Rotation;
        float Direction;
    };
    
    static transform Empty();
    static transform MakeFromVector(const V3 Location);
    static transform Make(const V3 Location, const V3 Rotation, const V3 Scale);
};

#endif