#include <iostream>
#include <fstream>
#include <string>
#include "vec3.h"

int main()
{

    vec3 vector1 = vec3(1, 0, 0);
    vec3 vector2 = vec3(0, 1, 0);

    double dp = vector2 * vector1;

    std::cout << dp << std::endl;

    vec3 vector3 = vec3(8, 5, 4);
    vec3 norm = vector3.normalise();
    std::cout << norm.x << " " << norm.y << " " << norm.z << std::endl;
    std::cout << norm.length();
    // std::ofstream out("image.ppm");

    // out << "P3\n";
    // out << "256 256\n";
    // out << "255\n";

    // std::string str = "";

    // std::cout << "Ray tracer starting..." << std::endl;
    // for(int i = 0; i < 256; i++) {
    //     for (int j = 0; j < 256; j++) {
    //         out << j << " ";
    //         out << i << " ";
    //         out << 0 << "\t";

    //     }
    //     out << "\n";
    // }
    // out.close();
    return 0;
}
