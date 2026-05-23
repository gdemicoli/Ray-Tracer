#include "Materials.h"

Materials::Materials(Vec3 colour, double reflectivity) : colour(colour), reflectivity(reflectivity)
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
};
