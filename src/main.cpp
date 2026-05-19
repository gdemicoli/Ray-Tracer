#include <iostream>
#include <fstream>
#include <string>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitRecord.h"
#include "Scene.h"
#include "Camera.h"
#include "Materials.h"

int main()
{

    std::ofstream out("image.ppm");

    out << "P3\n";
    out << "256 256\n";
    out << "255\n";

    std::string str = "";
    Scene scene = Scene();

    scene.addObject(Sphere(Vec3(128, -200, -50), 100, Materials(Vec3(100, 100, 0))));

    scene.addObject(Sphere(Vec3(128, -150, 125), 75, Materials(Vec3(0, 0, 130))));

    Vec3 eye = Vec3(128, 150, 200);

    Vec3 lightSource = Vec3(128, 0, 200); // chack shadows properly...
    Camera camera = Camera(eye, 256, 256);

    std::cout << "Ray tracer starting..." << std::endl;
    for (int i = 255; i > -1; i--)
    {
        for (int j = 255; j > -1; j--)
        {

            Ray ray = camera.getRay(i, j);
            HitRecord hitRecord = scene.sceneCollision(ray);
            // hitppoint from eye
            //  calculate hitpoint - lightsoutce,
            // gives me the direction the light is hitting the point at

            if (hitRecord.hit == true)
            {
                Ray lightRay = Ray(lightSource, hitRecord.hitPoint - lightSource);
                HitRecord shadow = scene.sceneCollision(Ray(hitRecord.hitPoint + hitRecord.normal * 0.001, lightSource - hitRecord.hitPoint));
                double brightness = (lightRay.direction.normalise() * -1) * hitRecord.normal;
                if (shadow.hit)
                {
                    out << (int)(hitRecord.materials.colour.x * 0.01) << " ";
                    out << (int)(hitRecord.materials.colour.y * 0.01) << " ";
                    out << (int)(hitRecord.materials.colour.z * 0.01) << "\t";
                }
                else if (brightness > 0)
                {
                    out << (int)(hitRecord.materials.colour.x * brightness) << " ";
                    out << (int)(hitRecord.materials.colour.y * brightness) << " ";
                    out << (int)(hitRecord.materials.colour.z * brightness) << "\t";
                }

                else
                {
                    out << 10 << " ";
                    out << 0 << " ";
                    out << 0 << "\t";
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
    return 0;
}
