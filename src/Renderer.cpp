#include <iostream>
#include <fstream>
#include <string>
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
// TO-DO:
// Change colors in main to use a 0.0 to 1.0 scale instead of 100, and alter PPM printer to multiply the final output by 255.

// Ensure sceneCollision isn't registering shadows from objects sitting behind light source point.

void Renderer::render(const std::string &outputFile)
{
    std::cout << "Ray tracer starting..." << std::endl;
    std::ofstream out(outputFile);

    out << "P3\n";
    out << "1024 1024\n";
    out << "255\n";
    int samples = 16;
    for (int i = 1023; i > -1; i--)
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
            if (i == 512 && j == 512)
            {
                std::cout << "accumulated: " << accumulated.x << " " << accumulated.y << " " << accumulated.z << std::endl;
            }
            Vec3 pixelColour = accumulated * (1.0 / samples);
            out << (int)(pixelColour.x * 255) << " ";
            out << (int)(pixelColour.y * 255) << " ";
            out << (int)(pixelColour.z * 255) << "\t";
        }
        out << "\n";
    }
    out.close();
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
        return Vec3(0, 0, 1);
    }
}
