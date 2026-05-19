#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Materials.h"
class Sphere
{
public:
    Vec3 centre;
    double radius;
    Materials materials;

    Sphere(Vec3 centre, double radius, Materials materials);
    HitRecord hit(const Ray &ray);
};