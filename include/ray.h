#pragma once
#include "vec3.h"

class ray
{
public:
    vec3 origin;
    vec3 direction;

    ray(vec3 origin, vec3 direction);
    vec3 at(double t);
};
