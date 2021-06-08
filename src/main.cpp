#include "../scene/triangle.hpp"
#include "../scene/sphere.hpp"
#include "../scene/light.hpp"
#include "../fps.hpp"
#include "../constants.hpp"

#include <thread>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

std::vector<std::unique_ptr<Shape>> shapes;
Light light = Light(Vec3f(0, 0, 3));

Vec3f camera(0, 0, 0);
// apparently these don't work
float pitch = 0;
float yaw = 1;

void makeQuad(std::vector<std::unique_ptr<Shape>> &list, const Vec3f &a, const Vec3f &b, const Vec3f &c, const Vec3f &d, const Vec3f &color)
{
    list.push_back(std::make_unique<Triangle>(Triangle(a, b, c, color)));
    list.push_back(std::make_unique<Triangle>(Triangle(a, c, d, color)));
}

// 0, 0 is screen center
// NOTE: y axis is inverteed
Ray getRay(int px, int py)
{
    Vec3f temp = Vec3f(RAY_DX * px, RAY_DY * py, 0).rotate(pitch, yaw);

    return Ray(camera, Vec3f(temp.x, temp.y, 1));
}

Vec3f getColor(Ray &ray)
{
    float minLen = INFINITY;
    Intersection *it;
    int indx = 0;

    for (int i = 0; i < shapes.size(); ++i)
    {
        Intersection intersect = shapes[i].get()->getIntersection(ray);

        if (!intersect.intersected)
            continue;
        
        float dist = ray.start.dist(intersect.hit);

        if (dist >= minLen)
            continue;

        minLen = dist;
        indx = i;
        it = &intersect;
    }

    if (std::isinf(minLen))
        return BACKGROUND;
    
    Shape *hit = shapes[indx].get();

    if (light.inShadow(*it, camera, shapes))
        return Vec3f(0);
    
    float intensity = it->normal.dot(Vec3f(0, 0, 1));
    return hit->getMat().color * intensity;
}

void initShapes()
{
    shapes.push_back(std::make_unique<Sphere>(
        Sphere(Vec3f(0, 0, 6), 1, Material(Vec3f(255, 0, 0)))));
}

void thread_func(sf::Uint8 *pixels, int xstart, int xend, int ystart, int yend, int thread_id)
{
    int index = (ystart * RES_X + xstart) * 4;
    const int xIndexRemain = (RES_X - (xend - xstart)) * 4;

    for (int y = ystart; y < yend; ++y)
    {
        for (int x = xstart; x < xend; ++x)
        {
            Ray temp = getRay(x - HALF_RES_X, y - HALF_RES_Y);

            Vec3f c = getColor(temp);

            pixels[index]   = c.x;
            pixels[index+1] = c.y;
            pixels[index+2] = c.z;
            pixels[index+3] = 255;

            index += 4;
        }

        index += xIndexRemain;
    }
}

int main(int argc, char *argv[])
{
    sf::RenderWindow win(sf::VideoMode(RES_X, RES_Y), "yes");

    FPSCounter fps;
    sf::Event e;

    sf::Uint8 *pixels = new sf::Uint8[RES_X * RES_Y * 4];
    sf::Texture texture;
    texture.create(RES_X, RES_Y);
    sf::Sprite texSprite(texture);

    initShapes();
    
    while (win.isOpen())
    {
        while (win.pollEvent(e))
            if (e.type == sf::Event::Closed)
                win.close();

        std::thread t1(thread_func, pixels, 0, RES_X, 0,          HALF_RES_Y, 1);
        std::thread t2(thread_func, pixels, 0, RES_X, HALF_RES_Y, RES_Y,      2);

        t1.join();
        t2.join();

        win.clear(sf::Color::White);

        texture.update(pixels);
        win.draw(texSprite);

        fps.update();
        fps.render(win);

        win.display();
    }

    return 0;
}


// int main()
// {
//     Vec3f v(0, 0, 1);
//     v.rotate(M_PI, 0).print();
// }
