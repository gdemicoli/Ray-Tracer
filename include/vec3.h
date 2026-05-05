#pragma once

class vec3
{
public:
    double x;
    double y;   
    double z;

    vec3(double x, double y, double z);

    vec3 operator+(const vec3 &other);
    vec3 operator-(const vec3 &other);
    vec3 operator*(const double other);
    double operator*(const vec3 &other);
    double length();
    vec3 normalise();
};