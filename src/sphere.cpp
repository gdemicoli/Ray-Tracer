#include "Sphere.h"
#include <cmath>
#include "HitRecord.h"
Sphere::Sphere(Vec3 centre, double radius)
    : centre(centre), radius(radius)
{
}

HitRecord Sphere::hit(const Ray &ray)
{
    double a = ray.direction * ray.direction; // dot product
    double b = (ray.origin - centre) * ray.direction * 2;
    double c = (ray.origin - centre) * (ray.origin - centre) - (radius * radius);
    double discriminant = (b * b) - 4 * a * c;
    if (discriminant < 0) // ray doesnt intersect
    {
        return HitRecord{false, -1, Vec3(0, 0, 0), Vec3(0, 0, 0)};
    }
    double t1 = (-1.0 * b + std::sqrt(discriminant)) / (2 * a);
    double t2 = (-1.0 * b - std::sqrt(discriminant)) / (2 * a);

    if (t2 > 0) // sphere is in front 
    {
        return HitRecord{true, t2, (ray.at(t2) - centre).normalise(), ray.at(t2)};
    }

    else if (t1 > 0) // inside sphere
    {
        return HitRecord{true, t1, (ray.at(t1) - centre).normalise(), ray.at(t1)};
    }

    else // sphere is behind, both are negative
    {
        return HitRecord{false, -1, (ray.at(t1) - centre).normalise(), ray.at(t1)};
    }
}