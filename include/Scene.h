#pragma once
#include "Sphere.h"
#include "Ray.h"
#include "HitRecord.h"
#include <vector>

class Scene
{
public:
    std::vector<Sphere> objects;

    Scene();
    void addObject(const Sphere &sphere);
    HitRecord sceneCollision(const Ray &ray);
};