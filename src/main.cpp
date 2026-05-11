#include <iostream>
#include <fstream>
#include <string>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"

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
            double brightness = sphere.hit(ray);
            // std::cout << brightness << std::endl;
            if (brightness <= 0)
            {
                out << 0 << " ";
                out << 0 << " ";
                out << 255 << "\t";
            }
            else
            {
                // std::cout << brightness << " " << 255 * brightness << std::endl;
                out << (int)(255 * brightness) << " ";
                out << 0 << " ";
                out << (int)(100 * brightness) << "\t";
            }
        }
        out << "\n";
    }
    out.close();
    return 0;
}
