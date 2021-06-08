#include "../../math/ray.hpp"

Ray::Ray(const Vec3f &start, const Vec3f &delta)
    : start(start), delta(delta.normalize()) {}

float Ray::getLambda(const Plane &plane) const
{
    float numer = plane.norm.dot(start) + plane.k;
    float denom = plane.norm.dot(delta);
    float lambda = -(numer/denom);

    return lambda;
}

Vec3f Ray::getIntersection(const Plane &plane) const
{
    return getPos(getLambda(plane));
}

Vec3f Ray::getPos(float lambda) const
{
    return delta * lambda + start;
}
