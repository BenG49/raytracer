#include "../include/scene/sphere.hpp"

#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"

const int XRES = 640;
const int YRES = 640;

const float XVIEWPLANE = 0.5f;
const float YVIEWPLANE = 0.375f;
const float RAYDX = XVIEWPLANE / XRES;
const float RAYDY = YVIEWPLANE / YRES;

const float VIEWPLANE_XSTART = -XVIEWPLANE/2.0f;
const float VIEWPLANE_YSTART = -YVIEWPLANE/2.0f;

const Vec3f BACKGROUND(255, 255, 255);

// TODO: fix rotation

Vec3f cam(0);
float pitch = 0;
float yaw = 0;

std::vector<std::unique_ptr<Shape>> shapes;

//
//
//

void initShapes()
{
    shapes.push_back(std::make_unique<Sphere>(
        Sphere(
            Vec3f(0, 0, 7),
            2,
            { Vec3f(255, 0, 0) }
        )
    ));
}

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

/*int main()
{
    sf::RenderWindow win(sf::VideoMode(XRES, YRES), ".");

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
}*/

int main()
{
    initShapes();

    Ray r = getRay(XRES/2, YRES/2);
    getColor(r).print();
}
