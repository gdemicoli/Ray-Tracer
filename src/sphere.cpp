#include "Sphere.h"
#include <cmath>
Sphere::Sphere(Vec3 centre, double radius)
    : centre(centre), radius(radius)
{
}

double Sphere::hit(const Ray &ray)
{
    double a = ray.direction * ray.direction; // dot product
    double b = (ray.origin - centre) * ray.direction * 2;
    double c = (ray.origin - centre) * (ray.origin - centre) - (radius * radius);
    double discriminant = (b * b) - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    double t1 = (-1.0 * b + std::sqrt(discriminant)) / (2 * a);
    double t2 = (-1.0 * b - std::sqrt(discriminant)) / (2 * a);

    if (t1 < t2 && t1 > 0)
    {
        Vec3 surfaceNormal = ray.at(t1) - centre;

        return (ray.direction.normalise() * -1) * surfaceNormal.normalise();
    }
    else if (t1 > t2 && t2 > 0)
    {
        Vec3 surfaceNormal = ray.at(t2) - centre;

        return (ray.direction.normalise() * -1) * surfaceNormal.normalise();
        }
    else
    {
        return -1.0;
    }
}