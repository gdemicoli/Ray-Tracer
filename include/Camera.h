#pragma once
#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
    Vec3 eyePos;
    int imageHeight;
    int imageWidth;

    Camera(Vec3 &eyePos, int imageHeight, int imageWidth);
    Ray getRay(int i, int j);
};
