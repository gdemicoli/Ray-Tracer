#include "Camera.h"

Camera::Camera(Vec3 &eyePos, int imageHeight, int imageWidth) : eyePos(eyePos), imageHeight(imageHeight), imageWidth(imageWidth) {
                                                                };

Ray Camera::getRay(double i, double j)
{

    return Ray(eyePos, Vec3(j, 0, i) - eyePos);
};