#include "Ray.h"

Ray::Ray(Vec3 origin, Vec3 direction)
    : origin(origin), direction(direction)
{
}

Vec3 Ray::at(double t) const{
    return origin + direction * t;
}