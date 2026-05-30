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
        try
        {
            if (std::string(argv[i]) == "--samples" && i + 1 < argc)
                samples = std::stoi(argv[++i]);
            else if (std::string(argv[i]) == "--width" && i + 1 < argc)
                width = std::stoi(argv[++i]);
            else if (std::string(argv[i]) == "--height" && i + 1 < argc)
                height = std::stoi(argv[++i]);
            else if (std::string(argv[i]) == "--output" && i + 1 < argc)
                output = argv[++i];
            else
            {
                std::cerr << "Unknown or incomplete argument: " << argv[i] << std::endl;
                return 1;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: invalid value for " << argv[i] << std::endl;
            return 1;
        }
    }

    if (width <= 0 || height <= 0)
    {
        std::cerr << "Error: width and height must be positive" << std::endl;
        return 1;
    }
    if (samples <= 0)
    {
        std::cerr << "Error: samples must be positive" << std::endl;
        return 1;
    }
    if (output.empty())
    {
        std::cerr << "Error: output filename cannot be empty" << std::endl;
        return 1;
    }

    Scene scene = Scene();

    scene.addObject(Sphere(Vec3(512, -800, 200), 400, Materials(Vec3(0.8, 0.2, 0.2), 0.2, 0.5)));  // big red, low reflect
    scene.addObject(Sphere(Vec3(200, -400, 600), 200, Materials(Vec3(0.2, 0.2, 0.8), 0.53, 0.2))); // blue, medium reflect
    scene.addObject(Sphere(Vec3(800, -300, 500), 150, Materials(Vec3(0.2, 0.8, 0.2), 0.05, 0.7))); // green, low reflect
    scene.addObject(Sphere(Vec3(400, -200, 800), 100, Materials(Vec3(0.8, 0.8, 0.2), 0.7, 0.05))); // yellow, high reflect

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
