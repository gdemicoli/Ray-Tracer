#pragma once
#include "Vec3.h"
class Materials
{
public:
    Vec3 colour;
    double reflectivity;
    double roughness;

    Materials(Vec3 colour, double reflectivity, double roughness);

};
