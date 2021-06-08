#pragma once

#include "vec3.hpp"
#include "plane.hpp"

struct Ray
{
    Ray(const Vec3f &start, const Vec3f &delta);
    
    float getLambda(const Plane &plane) const;
    Vec3f getIntersection(const Plane &plane) const;
    Vec3f getPos(float lambda) const;

    Vec3f start;
    Vec3f delta;
};