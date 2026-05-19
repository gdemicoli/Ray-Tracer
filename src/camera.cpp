#include "Camera.h"

Camera::Camera(Vec3 &eyePos, int imageHeight, int imageWidth) : eyePos(eyePos), imageHeight(imageHeight), imageWidth(imageWidth) {
                                                                };

Ray Camera::getRay(int i, int j)
{

    return Ray(eyePos, Vec3(j, 0, i) - eyePos);
};