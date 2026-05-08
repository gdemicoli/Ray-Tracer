#pragma once

class vec3
{
public:
    double x;
    double y;   
    double z;

    vec3(double x, double y, double z);

    vec3 operator+(const vec3 &other) const;
    vec3 operator-(const vec3 &other) const;
    vec3 operator*(const double other) const;
    double operator*(const vec3 &other) const;
    double length() const;
    vec3 normalise() const;
};