#include "../../scene/sphere.hpp"
#include <iostream>

Sphere::Sphere(const Vec3f &center, float radius, const Material &m)
    : center(center)
    , radius(radius)
    , r2(radius*radius)
    , m(m) {}

// from myles because I have no idea how this works
Intersection Sphere::getIntersection(const Ray &ray) const
{
    Vec3f l = center - ray.start;
    float tca = l.dot(ray.delta);
    if (tca < 0) return MISSED;
    float d2 = l.dot(l) - tca * tca;
    if (d2 > r2) return MISSED;
    float thc = std::sqrt(r2 - d2);
    
    float t0 = tca - thc;

    if (t0 <= 0) return MISSED;

    Vec3f hit = ray.getPos(t0);
    return { true, hit, (hit - center).normalize() };
}

Material Sphere::getMat() const { return m; }
