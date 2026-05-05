#include "vec3.h"
#include <cmath>

vec3::vec3(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

vec3 vec3::operator+(const vec3 &other)
{
    return vec3(x + other.x, y + other.y, z + other.z);
}

vec3 vec3::operator-(const vec3 &other)
{
    return vec3(x - other.x, y - other.y, z - other.z);
}

vec3 vec3::operator*(const double other) // scalar multiplication
{
    return vec3(x * other, y * other, z * other);
}

double vec3::operator*(const vec3 &other) // dot product
{
    return x * other.x + y * other.y + z * other.z;
}

double vec3::length()
{
    return std::sqrt(x * x + y * y + z * z);
}

vec3 vec3::normalise()
{
    double len = length();

    return vec3(x / len, y / len, z / len);
}
