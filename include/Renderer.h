#pragma once
#include <random>
#include <thread>
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"


class Renderer
{
public:
    Renderer(Scene scene, Camera camera, Vec3 lightSource);
    void render(const std::string &outputFile);
    void renderSection(int startRow, int endRow, std::vector<std::vector<Vec3>> &buffer);

private:
    Scene scene;
    Camera camera;
    Vec3 lightSource;
    Vec3 getColour(Ray ray, double depth);
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
};