#pragma once
#include <random>
#include <thread>
#include <atomic>
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"

class Renderer
{
public:
    Renderer(Scene scene, Camera camera, Vec3 lightSource, int samples);
    void render(const std::string &outputFile);
    void renderSection(int startRow, int endRow, std::vector<std::vector<Vec3>> &buffer);

private:
    Scene scene;
    Camera camera;
    Vec3 lightSource;
    int samples;
    Vec3 getColour(Ray ray, double depth);
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    std::atomic<int> completedRows{0};
    std::mutex printMutex;
};