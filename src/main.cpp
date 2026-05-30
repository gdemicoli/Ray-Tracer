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
#include "Renderer.h"
#include <chrono>

int main(int argc, char *argv[])
{
    int width = 1024;
    int height = 1024;
    int samples = 16;
    std::string output = "image.ppm";
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "--samples")
        {
            samples = std::stoi(argv[i + 1]);
        }

        else if (std::string(argv[i]) == "--width")
        {
            width = std::stoi(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "--height")
        {
            height = std::stoi(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "--output")
        {
            output = argv[i + 1];
        }
    }

    Scene scene = Scene();

    scene.addObject(Sphere(Vec3(512, -800, 200), 400, Materials(Vec3(0.8, 0.2, 0.2), 0.9, 0)));    // big red, low reflect
    scene.addObject(Sphere(Vec3(200, -400, 600), 200, Materials(Vec3(0.2, 0.2, 0.8), 0.3, 0.1))); // blue, medium reflect
    scene.addObject(Sphere(Vec3(800, -300, 500), 150, Materials(Vec3(0.2, 0.8, 0.2), 0.1, 0.9)));  // green, no reflect
    scene.addObject(Sphere(Vec3(400, -200, 800), 100, Materials(Vec3(0.8, 0.8, 0.2), 0.9, 0.9)));  // yellow, mirror

    Vec3 eye = Vec3(512, 800, 1200);
    Vec3 lightSource = Vec3(200, 1000, 1500);
    Camera camera = Camera(eye, width, height);

    Renderer renderer(scene, camera, lightSource, samples);

    std::cout << "Starting render (" << width << "x" << height << ", " << samples << " samples)..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    renderer.render(output);

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Render time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms" << std::endl;

    return 0;
}
