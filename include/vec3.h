#pragma once

class vec3
{
public:
    double x;
    double y;   
    double z;

    vec3(double x, double y, double z);

    vec3 operator+(const vec3 &other) const; //vector addition
    vec3 operator-(const vec3 &other) const; //vector subtraction
    vec3 operator*(const double other) const; //scalar multiplication
    double operator*(const vec3 &other) const; //dot product
    double length() const; // magnitude
    vec3 normalise() const; // unit vector
};