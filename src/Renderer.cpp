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
            
            Ray ray = camera.getRay(i, j);                   // retrieves ray from eye to pixel
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
                    out << (int)(hitRecord.materials.colour.x * 0.01) << " ";
                    out << (int)(hitRecord.materials.colour.y * 0.01) << " ";
                    out << (int)(hitRecord.materials.colour.z * 0.01) << "\t";
                }
                else if (brightness > 0) // hit by light
                {
                    out << (int)(hitRecord.materials.colour.x * brightness) << " ";
                    out << (int)(hitRecord.materials.colour.y * brightness) << " ";
                    out << (int)(hitRecord.materials.colour.z * brightness) << "\t";
                }

                else // not facing light
                {
                    out << (int)(hitRecord.materials.colour.x * 0.05) << " ";
                    out << (int)(hitRecord.materials.colour.y * 0.05) << " ";
                    out << (int)(hitRecord.materials.colour.z * 0.05) << "\t";
                }
            }

            else
            {
                out << 0 << " ";
                out << 0 << " ";
                out << 255 << "\t";
            }
        }
        out << "\n";
    }
    out.close();
}