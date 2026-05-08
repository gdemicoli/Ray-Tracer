#include "ray.h"

ray::ray(vec3 origin, vec3 direction)
    : origin(origin), direction(direction)
{
}

vec3 ray::at(double t){
    return origin + direction * t;
}