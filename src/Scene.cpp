#include "Scene.h"
#include "Sphere.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Materials.h"
#include <vector>

Scene::Scene() {}

void Scene::addObject(const Sphere &sphere)
{
    objects.push_back(sphere);
}

HitRecord Scene::sceneCollision(const Ray &ray)
{

    HitRecord closest = HitRecord{false, 0, Vec3(0, 0, 0), Vec3(0, 0, 0), Materials(Vec3(0, 0, 0), 0, 0)};
    for (Sphere obj : objects)
    {
        HitRecord hit = obj.hit(ray);

        if (hit.hit && ((hit.tValue < closest.tValue) or !closest.hit))
        {
            closest = hit;
        }
    }

    return closest;
}
