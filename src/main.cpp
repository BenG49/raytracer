#include "../include/scene/sphere.hpp"
#include "../include/scene/light.hpp"
#include "constants.hpp"

#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"

//
//
//

Vec3f cam(0, 0, 0);
float pitch = 0;
float yaw = 0;

std::vector<std::unique_ptr<Shape>> shapes;
std::vector<std::unique_ptr<Light>> lights;

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

Vec3f castRay(const Ray &ray, int depth)
{
    float minDist = INFINITY;
    Intersection intr;
    int index = 0;
    
    for (int i = 0; i < shapes.size(); ++i)
    {
        Intersection intersect = shapes[i].get()->getIntersection(ray);

        if (!intersect.intersected)
            continue;
        
        float dist = ray.origin.dist(intersect.hit);

        if (dist >= minDist)
            continue;
        
        minDist = dist;
        index = i;
        intr = intersect;
    }

    if (std::isinf(minDist))
    {
        if (ray.delta.y <= 0) return BACKGROUND;

        float t = (3 - ray.origin.y) / ray.delta.y;
        Vec3f pos = ray.getPos(t);
        if (std::fmod(std::abs(pos.z), 4.0f) > 2 == std::fmod(std::abs(pos.x), 4.0f) > 2) return BACKGROUND;
        return Vec3f(100);
    }

    if (depth < MAX_DEPTH && shapes[index].get()->getMat().reflective)
        return castRay(ray.reflect(intr), depth+1);

    bool inShadow = true;
    for (int i = 0; i < lights.size(); ++i)
    {
        if (!lights[i].get()->inShadow(intr, cam, shapes))
        {
            inShadow = false;
            break;
        }
    }

    if (inShadow)
        return ORIG; // Vec3f(0)
    
    return shapes[index].get()->getMat().color * (1.0f / lights[0].get()->pos.dist(intr.hit));
}

void drawFrame(sf::Uint8 *pixels)
{
    int index = 0;
    for (int y = 0; y < YRES; ++y)
    {
        for (int x = 0; x < XRES; ++x)
        {
            Ray temp = getRay(x, y);
            Vec3f color = castRay(temp, 0);

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
        Sphere(Vec3f(0, 0, 7),
               1,
               { Vec3f(255, 0, 0), false })));

    shapes.push_back(std::make_unique<Sphere>(
        Sphere(Vec3f(-1, 0, 6),
               0.3,
               { Vec3f(0, 100, 50), true })));

    lights.push_back(std::make_unique<Light>(
        Light(Vec3f(0, 0, 5),
              Vec3f(1, 1, 1))));
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
        {
            if (e.type == sf::Event::Closed)
                win.close();
            else if (e.type == sf::Event::KeyPressed)
            {
                int code = e.key.code;

                if (code == sf::Keyboard::Escape)
                    win.close();
                
                if (code == sf::Keyboard::W)
                    cam += Vec3f(0, 0, 1).rotate(pitch, yaw);
                if (code == sf::Keyboard::S)
                    cam -= Vec3f(0, 0, 1).rotate(pitch, yaw);
                
                if (code == sf::Keyboard::A)
                    yaw -= 0.1;
                if (code == sf::Keyboard::D)
                    yaw += 0.1;
            }
        }
        
        drawFrame(pixels);

        win.clear();
        
        tex.update(pixels);
        win.draw(texSprite);

        win.display();
    }

    return 0;
}
