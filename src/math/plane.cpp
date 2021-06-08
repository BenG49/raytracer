#include "../../math/plane.hpp"

Plane::Plane(const Vec3f &norm, float k)
    : norm(norm), k(k) {}

Plane::Plane(const Vec3f &a, const Vec3f &b, const Vec3f &c)
    : norm((c - a).cross(b - a))
    , k((norm * -1.0f).dot(c)) {}

Plane::Plane(const Vec3f &norm, const Vec3f &point)
    : norm(norm)
    , k((norm * -1.0f).dot(point)) {}

bool Plane::onPlane(const Vec3f &vec) const
{
    return norm.dot(vec) + k == 0;
}

bool Plane::pointsSameSidePlane(const Vec3f &a, const Vec3f &b) const
{
    float i = norm.dot(a) + k;
    float j = norm.dot(b) + k;

    if (i < 0 && j < 0)
        return true;

    if (i > 0 && j > 0)
        return true;

    return false;
}
