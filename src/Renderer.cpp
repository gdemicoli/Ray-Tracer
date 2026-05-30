#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <atomic>
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"

Renderer::Renderer(Scene scene, Camera camera, Vec3 lightSource, int samples)
    : scene(scene), camera(camera), lightSource(lightSource), samples(samples),
      rng(42), dist(-0.5, 0.5)
{
}

void Renderer::render(const std::string &outputFile)
{
    std::vector<std::vector<Vec3>> buffer(camera.imageHeight, std::vector<Vec3>(camera.imageWidth, Vec3(0, 0, 0)));
    std::vector<std::thread> threads;

    int rowsPerThread = camera.imageHeight / 10;

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
    out << camera.imageWidth << " " << camera.imageHeight << "\n";
    out << "255\n";

    for (int i = camera.imageHeight - 1; i >= 0; i--)
    {
        for (int j = camera.imageWidth - 1; j >= 0; j--)
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

    for (int i = startRow; i < endRow; i++)
    {
        for (int j = camera.imageWidth - 1; j > -1; j--)
        {
            Vec3 accumulated = Vec3(0, 0, 0);

            for (int s = 0; s < samples; s++)
            {
                double di = i + dist(rng);
                double dj = j + dist(rng);
                accumulated = accumulated + getColour(camera.getRay(di, dj), 10);
            }

            buffer[i][j] = accumulated * (1.0 / samples);
            completedRows++;
            if (completedRows % camera.imageWidth == 0)
            {
                std::lock_guard<std::mutex> lock(printMutex);
                int percent = (completedRows * 100) / (camera.imageHeight * camera.imageWidth);
                std::cout << "\rProgress: " << percent << "%" << std::flush;
            }
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
        Vec3 reflected = ray.direction.reflect(hitRecord.normal);
        Vec3 roughReflected = (reflected + randomUnitSphere() * hitRecord.materials.roughness).normalise();
        Ray reflectionRay = Ray(hitRecord.hitPoint + hitRecord.normal * 0.001, roughReflected);

        Ray lightRay = Ray(lightSource, hitRecord.hitPoint - lightSource);
        HitRecord shadow = scene.sceneCollision(Ray(hitRecord.hitPoint + hitRecord.normal * 0.001, lightSource - hitRecord.hitPoint));
        double brightness = (lightRay.direction.normalise() * -1) * hitRecord.normal;
        Vec3 surfaceColour(0, 0, 0);

        double distanceToLight = (lightSource - hitRecord.hitPoint).length();

        double ambient = 0.05;
        double lit = std::max(brightness, ambient);
        surfaceColour = hitRecord.materials.colour * lit;

        if (shadow.hit && shadow.tValue < distanceToLight)
        {
            surfaceColour = hitRecord.materials.colour * ambient;
        }
        else
        {
            double lit = std::max(brightness, ambient);
            surfaceColour = hitRecord.materials.colour * lit;
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
        double t = std::clamp(0.5 * (-ray.direction.normalise().y + 1.0), 0.0, 1.0);
        return Vec3(0.7, 0.8, 1.0) * (1 - t) + Vec3(0.2, 0.4, 0.9) * t;
    }
}

Vec3 Renderer::randomUnitSphere()
{
    std::uniform_real_distribution<double> d(-1.0, 1.0);
    while (true)
    {
        Vec3 v(d(rng), d(rng), d(rng));
        if (v.length() <= 1.0)
            return v;
    }
}
