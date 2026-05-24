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

int main()
{

    Scene scene = Scene();

    scene.addObject(Sphere(Vec3(128, -200, -50), 100, Materials(Vec3(100, 0, 0), 0.5)));

    scene.addObject(Sphere(Vec3(128, -150, 125), 75, Materials(Vec3(0, 100, 0), 0.2)));

    Vec3 eye = Vec3(128, 200, 200);

    Vec3 lightSource = Vec3(128, 0, 200); // chack shadows properly...
    Camera camera = Camera(eye, 256, 256);
    Renderer renderer(scene, camera, lightSource);
    renderer.render("image.ppm");

    return 0;
}
