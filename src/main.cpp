#include <iostream>
#include <fstream>
#include <string>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitRecord.h"

int main()
{

    std::ofstream out("image.ppm");

    out << "P3\n";
    out << "256 256\n";
    out << "255\n";

    std::string str = "";

    Sphere sphere = Sphere(Vec3(128, 128, 10), 70);
    Vec3 eye = Vec3(128, 128, -100);

    std::cout << "Ray tracer starting..." << std::endl;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            Vec3 pixel = Vec3(i, j, 0);
            Ray ray = Ray(eye, pixel - eye);
            HitRecord hitRecord = sphere.hit(ray);
            double brightness = (ray.direction.normalise() * -1) * hitRecord.normal;

            if (hitRecord.hit == true && brightness > 0)
            {

                out << (int)(100 * brightness) << " ";
                out << 0 << " ";
                out << (int)(0) << "\t";
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
