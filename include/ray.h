#pragma once
#include "Vec3.h"

class Ray
{
public:
    Vec3 origin;
    Vec3 direction;

    Ray(Vec3 origin, Vec3 direction);
    Vec3 at(double t) const;
};
