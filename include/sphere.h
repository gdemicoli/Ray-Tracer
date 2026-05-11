#pragma once
#include "Vec3.h"
#include "Ray.h"

class Sphere
{
public:
    Vec3 centre;
    double radius;

    Sphere(Vec3 centre, double radius);
    double hit(const Ray& ray);
};