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

    scene.addObject(Sphere(Vec3(128, -200, -50), 100));

    scene.addObject(Sphere(Vec3(128, -150, 125), 75));

    Vec3 eye = Vec3(128, 100, 128);

    Vec3 lightSource = Vec3(128, 0, 200); // chack shadows properly...

    std::cout << "Ray tracer starting..." << std::endl;
    for (int i = 255; i > -1; i--)
    {
        for (int j = 255; j > -1; j--)
        {

            Vec3 pixel = Vec3(j, 0, i);
            Ray ray = Ray(eye, pixel - eye);
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
                    out << 20 << " ";
                    out << 0 << " ";
                    out << 0 << "\t";
                }
                else if (brightness > 0)
                {
                    out << (int)(255 * brightness) << " ";
                    out << 0 << " ";
                    out << (int)(0) << "\t";
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
