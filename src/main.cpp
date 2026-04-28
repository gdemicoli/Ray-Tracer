#include <iostream>
#include <fstream>
#include <string>

int main() {
    
    std::ofstream out("image.ppm");

    out << "P3\n";
    out << "256 256\n";
    out << "255\n";

    std::string str = "";


    std::cout << "Ray tracer starting..." << std::endl;
    for(int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            out << j << " ";
            out << i << " ";
            out << 0 << "\t";

        }
        out << "\n";
    }
    out.close();
    return 0;
}

