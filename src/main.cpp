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

    scene.addObject(Sphere(Vec3(700, -1000, 0), 300, Materials(Vec3(0.5, 0, 0), 0.5)));// red

    scene.addObject(Sphere(Vec3(200, -500, 500), 500, Materials(Vec3(0, 0.5, 0), 0.2)));//green

    Vec3 eye = Vec3(500, 1500, 500); //done

    Vec3 lightSource = Vec3(500, 500, 1500); //done
    Camera camera = Camera(eye, 1024, 1024);
    Renderer renderer(scene, camera, lightSource);
    renderer.render("image.ppm");

    return 0;
}
