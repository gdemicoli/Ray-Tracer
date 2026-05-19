#pragma once
#include "Vec3.h"
#include "Materials.h"

struct HitRecord
{
    bool hit;
    double tValue; // How far along the ray an object was hit
    Vec3 normal;   // Direction an object is facing (surface normal)
    Vec3 hitPoint; // 3d position where the ray hit the sphere
    Materials materials;
};