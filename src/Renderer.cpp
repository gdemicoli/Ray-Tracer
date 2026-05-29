#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"

Renderer::Renderer(Scene scene, Camera camera, Vec3 lightSource)
    : scene(scene), camera(camera), lightSource(lightSource),
      rng(42), dist(-0.5, 0.5)
{
}

void Renderer::render(const std::string &outputFile)
{
    std::vector<std::vector<Vec3>> buffer(1024, std::vector<Vec3>(1024, Vec3(0, 0, 0)));
    std::vector<std::thread> threads;

    int rowsPerThread = 1024 / 10;

    for (int t = 0; t < 10; t++)
    {
        int startRow = t * rowsPerThread;
        int endRow = startRow + rowsPerThread;
        threads.push_back(std::thread(&Renderer::renderSection, this, startRow, endRow, std::ref(buffer)));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    std::ofstream out(outputFile);

    out << "P3\n";
    out << "1024 1024\n";
    out << "255\n";

    for (int i = 1023; i >= 0; i--)
    {
        for (int j = 1023; j >= 0; j--)
        {
            out << (int)(buffer[i][j].x * 255) << " ";
            out << (int)(buffer[i][j].y * 255) << " ";
            out << (int)(buffer[i][j].z * 255) << "\t";
        }
        out << "\n";
    }

    out.close();
}

void Renderer::renderSection(int startRow, int endRow, std::vector<std::vector<Vec3>> &buffer)
{
    int samples = 16;
    for (int i = startRow; i < endRow; i++)
    {
        for (int j = 1023; j > -1; j--)
        {
            Vec3 accumulated = Vec3(0, 0, 0);

            for (int s = 0; s < samples; s++)
            {
                double di = i + dist(rng);
                double dj = j + dist(rng);
                accumulated = accumulated + getColour(camera.getRay(di, dj), 10);
            }

            buffer[i][j] = accumulated * (1.0 / samples);
        }
    }
}

Vec3 Renderer::getColour(Ray ray, double depth)
{

    HitRecord hitRecord = scene.sceneCollision(ray); // checks if ray hits anything in the scene

    // hitppoint from eye
    //  calculate hitpoint - lightsoutce,
    // gives me the direction the light is hitting the point at

    if (hitRecord.hit == true) // we can see something
    {
        Ray reflectionRay = Ray(hitRecord.hitPoint + hitRecord.normal * 0.001, ray.direction.reflect(hitRecord.normal));

        Ray lightRay = Ray(lightSource, hitRecord.hitPoint - lightSource);
        HitRecord shadow = scene.sceneCollision(Ray(hitRecord.hitPoint + hitRecord.normal * 0.001, lightSource - hitRecord.hitPoint));
        double brightness = (lightRay.direction.normalise() * -1) * hitRecord.normal;
        Vec3 surfaceColour(0, 0, 0);

        double distanceToLight = (lightSource - hitRecord.hitPoint).length();

        if (shadow.hit && shadow.tValue < distanceToLight) // in shadow
        {
            surfaceColour = hitRecord.materials.colour * 0.1;
        }
        else if (brightness > 0) // hit by light
        {
            surfaceColour = hitRecord.materials.colour * brightness;
        }

        else // not facing light
        {
            surfaceColour = hitRecord.materials.colour * 0.05;
        }

        if (hitRecord.materials.reflectivity > 0 && depth > 0)
        {
            return surfaceColour * (1 - hitRecord.materials.reflectivity) + getColour(reflectionRay, depth - 1) * hitRecord.materials.reflectivity;
        }
        else
        {
            return surfaceColour;
        }
    }

    else
    {
        double t = 0.5 * (ray.direction.normalise().z + 1.0);
        return Vec3(1, 1, 1) * (1 - t) + Vec3(0.5, 0.7, 1.0) * t;
        // return Vec3(0, 0, 1);
    }
}
