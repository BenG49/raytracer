#include "../../scene/triangle.hpp"

Triangle::Triangle(const Vec3f &a, const Vec3f &b, const Vec3f &c, const Material &color)
    : a(a), b(b), c(c), color(color), plane(a, b, c) {}

Intersection Triangle::getIntersection(const Ray &ray) const
{
    if (ray.getLambda(plane) <= 0)
        return MISSED;

    Vec3f planeIntersect = ray.getIntersection(plane);

    for (int i = 0; i < 3; ++i)
        if (!axisWithinBounds(planeIntersect, i))
            return MISSED;
        
    if (!pointsSameSideLine(planeIntersect, a, b, c))
        return MISSED;
    if (!pointsSameSideLine(planeIntersect, b, a, c))
        return MISSED;
    if (!pointsSameSideLine(planeIntersect, c, a, b))
        return MISSED;
    
    return { true, planeIntersect, plane.norm };
}

Material Triangle::getMat() const { return color; }

bool Triangle::axisWithinBounds(const Vec3f &planeIntersection, int i) const
{
    if (planeIntersection[i] < min(a[i], b[i], c[i]))
        return false;

    if (planeIntersection[i] > max(a[i], b[i], c[i]))
        return false;

    return true;
}

bool Triangle::pointsSameSideLine(Vec3f a, Vec3f b, Vec3f lA, Vec3f lB) const
{
    Vec3f v = lA - lB;
    Vec3f i = v.cross(a - lB);
    Vec3f j = v.cross(b - lB);

    return i.dot(j) >= 0;
}

float Triangle::min(float x, float y, float z) const
{
    return std::min(std::min(x, y), z);
}
float Triangle::max(float x, float y, float z) const
{
    return std::max(std::max(x, y), z);
}
