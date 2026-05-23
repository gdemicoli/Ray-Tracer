#include <iostream>
#include <fstream>
#include <string>
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"

Renderer::Renderer(Scene scene, Camera camera, Vec3 lightSource) : scene(scene), camera(camera), lightSource(lightSource)
{
}
// Add ref;ection logic next
void Renderer::render(const std::string &outputFile)
{
    std::cout << "Ray tracer starting..." << std::endl;
    std::ofstream out(outputFile);

    out << "P3\n";
    out << "256 256\n";
    out << "255\n";
    for (int i = 255; i > -1; i--)
    {
        for (int j = 255; j > -1; j--)
        {
            Vec3 pixelColour = getColour(camera.getRay(i, j), 5);  // retrieves ray from eye to pixel
            out << (int)pixelColour.x << " ";
            out << (int)pixelColour.y << " ";
            out << (int)pixelColour.z << "\t";
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
        Ray lightRay = Ray(lightSource, hitRecord.hitPoint - lightSource);
        HitRecord shadow = scene.sceneCollision(Ray(hitRecord.hitPoint + hitRecord.normal * 0.001, lightSource - hitRecord.hitPoint));
        double brightness = (lightRay.direction.normalise() * -1) * hitRecord.normal;
        if (shadow.hit) // in shadow
        {
            return Vec3(hitRecord.materials.colour.x *0.1, hitRecord.materials.colour.y *0.1, hitRecord.materials.colour.z *0.1);
        }
        else if (brightness > 0) // hit by light
        {
            return Vec3(hitRecord.materials.colour.x * brightness, hitRecord.materials.colour.y * brightness, hitRecord.materials.colour.z * brightness);
        }

        else // not facing light
        {
            return Vec3(hitRecord.materials.colour.x * 0.05, hitRecord.materials.colour.y * 0.05, hitRecord.materials.colour.z * 0.05);
        }
    }

    else
    {
        return Vec3(0,0,255);
    }
}