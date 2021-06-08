#pragma once

#include "../src/math/vec3.cpp"

class Plane
{
public:
    Plane(const Vec3f &norm, float k);
    Plane(const Vec3f &a, const Vec3f &b, const Vec3f &c);
    Plane(const Vec3f &norm, const Vec3f &point);

    bool onPlane(const Vec3f &vec) const;
    bool pointsSameSidePlane(const Vec3f &a, const Vec3f &b) const;

    Vec3f norm;
    float k;
};
