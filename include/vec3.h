#pragma once

class Vec3
{
public:
    double x;
    double y;   
    double z;

    Vec3(double x, double y, double z);

    Vec3 operator+(const Vec3 &other) const; //vector addition
    Vec3 operator-(const Vec3 &other) const; //vector subtraction
    Vec3 operator*(const double other) const; //scalar multiplication
    double operator*(const Vec3 &other) const; //dot product
    double length() const; // magnitude
    Vec3 normalise() const; // unit vector
};