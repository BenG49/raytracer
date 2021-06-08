#include "../include/scene/sphere.hpp"
#include "../include/scene/light.hpp"

#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"

// CONSTANTS

const int XRES = 640;
const int YRES = 480;

const float XVIEWPLANE = 0.5f;
// keep view plane in same ratio as resolution
const float YVIEWPLANE = (YRES / (float) XRES) * XVIEWPLANE;
const float RAYDX = XVIEWPLANE / XRES;
const float RAYDY = YVIEWPLANE / YRES;

const float VIEWPLANE_XSTART = -XVIEWPLANE/2.0f;
const float VIEWPLANE_YSTART = -YVIEWPLANE/2.0f;

const Vec3f BACKGROUND(255, 255, 255);

//
//
// 

Vec3f cam(0);
float pitch = 0;
float yaw = 0;

std::vector<std::unique_ptr<Shape>> shapes;
Light light(Vec3f(0, 0, 5), Vec3f(1, 1, 1));

//
//
//

Ray getRay(int px, int py)
{
    Vec3f delta = Vec3f(VIEWPLANE_XSTART + RAYDX * px, VIEWPLANE_YSTART + RAYDY * py, 1)
        .rotate(pitch, yaw)
        .normalize();

    return Ray(cam, delta);
}

Vec3f getColor(const Ray &ray)
{
    float minDist = INFINITY;
    Intersection *intr;
    int index = 0;
    
    for (int i = 0; i < shapes.size(); ++i)
    {
        auto intersect = shapes[i].get()->getIntersection(ray);

        if (!intersect.intersected)
            continue;
        
        float dist = ray.origin.dist(intersect.hit);

        if (dist >= minDist)
            continue;
        
        minDist = dist;
        index = i;
        intr = &intersect;
    }

    if (std::isinf(minDist))
        return BACKGROUND;
    
    Shape *hit = shapes[index].get();

    if (light.inShadow(*intr, cam, shapes))
        return ORIG;
    
    float dist = intr->hit.dist(light.pos);

    return hit->getMat().color;
}

void drawFrame(sf::Uint8 *pixels)
{
    int index = 0;
    for (int y = 0; y < YRES; ++y)
    {
        for (int x = 0; x < XRES; ++x)
        {
            Ray temp = getRay(x, y);
            Vec3f color = getColor(temp);

            pixels[index]   = color.x;
            pixels[index+1] = color.y;
            pixels[index+2] = color.z;
            pixels[index+3] = 255;

            index += 4;
        }
    }
}

void initShapes()
{
    shapes.push_back(std::make_unique<Sphere>(
        Sphere(
            Vec3f(0, 0, 7),
            1,
            { Vec3f(255, 0, 0) }
        )
    ));
}

int main()
{
    sf::RenderWindow win(sf::VideoMode(XRES, YRES), "");

    sf::Event e;

    sf::Uint8 *pixels = new sf::Uint8[XRES * YRES * 4];
    sf::Texture tex;
    tex.create(XRES, YRES);
    sf::Sprite texSprite(tex);

    initShapes();

    while (win.isOpen())
    {
        while (win.pollEvent(e))
            if (e.type == sf::Event::Closed)
                win.close();
        
        drawFrame(pixels);

        win.clear();
        
        tex.update(pixels);
        win.draw(texSprite);

        win.display();
    }

    return 0;
}
