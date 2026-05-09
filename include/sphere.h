#pragma once
#include "vec3.h"
#include "ray.h"

class sphere
{
public:
    vec3 centre;
    double radius;

    sphere(vec3 centre, double radius);
    double hit(const ray& ray);
};