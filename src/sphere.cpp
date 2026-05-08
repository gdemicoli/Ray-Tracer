#include "sphere.h"

sphere::sphere(vec3 centre, double radius)
    : centre(centre), radius(radius)
{
}

vec3 sphere::hit(const ray &ray)
{
    double a = ray.direction * ray.direction;
    double b = (ray.origin - centre) * ray.direction * 2;
    double c = (ray.origin - centre) * (ray.origin - centre) - (radius * radius);

    // Add quadratic formula here next...
}