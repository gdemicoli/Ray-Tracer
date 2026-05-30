#include "Vec3.h"
#include <cmath>

Vec3::Vec3(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

Vec3 Vec3::operator+(const Vec3 &other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const double other) const // scalar multiplication
{
    return Vec3(x * other, y * other, z * other);
}

double Vec3::operator*(const Vec3 &other) const // dot product
{
    return x * other.x + y * other.y + z * other.z;
}

double Vec3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalise() const
{
    double len = length();

    return Vec3(x / len, y / len, z / len);
}

Vec3 Vec3::reflect(Vec3 &surfaceNorm) const
{
    Vec3 normD = (*this).normalise();     // normalise ray direction
    Vec3 normN = surfaceNorm.normalise(); // normalise surface normal
    double dp = normD * normN;            // dot product
    return normD - normN * 2 * dp;        // D - 2(D·N)N
}