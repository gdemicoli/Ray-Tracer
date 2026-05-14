#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "HitRecord.h"
class Sphere
{
public:
    Vec3 centre;
    double radius;

    Sphere(Vec3 centre, double radius);
    HitRecord hit(const Ray& ray);
};