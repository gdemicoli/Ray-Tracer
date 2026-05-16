#include <iostream>
#include <fstream>
#include <string>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitRecord.h"
#include "Scene.h"

int main()
{

    std::ofstream out("image.ppm");

    out << "P3\n";
    out << "256 256\n";
    out << "255\n";

    std::string str = "";
    Scene scene = Scene();

    for (int i = 1; i < 2; i++)
    {
        scene.addObject(Sphere(Vec3(32 * i, 128, 10), 70));
    }
    Vec3 eye = Vec3(256, 256, -100);
    Vec3 lightSource = Vec3(400, -200, -100);

    std::cout << "Ray tracer starting..." << std::endl;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            Vec3 pixel = Vec3(i, j, 0);
            Ray ray = Ray(eye, pixel - eye);
            HitRecord hitRecord = scene.sceneCollision(ray);
            // hitppoint from eye
            //  calculate hitpoint - lightsoutce,
            // gives me the direction the light is hitting the point at
            Ray lightRay = Ray(lightSource, hitRecord.hitPoint - lightSource);
            double brightness = (lightRay.direction.normalise() * -1) * hitRecord.normal;

            if (hitRecord.hit == true && brightness > 0)
            {

                out << (int)(255 * brightness) << " ";
                out << 0 << " ";
                out << (int)(0) << "\t";
            }
            else if (hitRecord.hit == true)
            {
                out << 20 << " ";
                out << 0 << " ";
                out << 0 << "\t";
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
