#include "Materials.h"

Materials::Materials(Vec3 colour, double reflectivity, double roughness) : colour(colour), reflectivity(reflectivity), roughness(roughness)
{
    if (reflectivity < 0.0)
    {
        this->reflectivity = 0.0;
    }
    else if (reflectivity > 1.0)
    {
        this->reflectivity = 1.0;
    }
    else
    {
        this->reflectivity = reflectivity;
    }

    if (roughness < 0.0)
    {
        this->roughness = 0.0;
    }
    else if (roughness > 1.0)
    {
        this->roughness = 1.0;
    }
    else
    {
        this->roughness = roughness;
    }
};
