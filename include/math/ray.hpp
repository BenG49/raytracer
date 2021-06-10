#pragma once

#include "../../src/math/vec3.cpp"
#include "../scene/intersection.hpp"

struct Ray
{
    Ray(const Vec3f &origin, const Vec3f &delta)
        : origin(origin), delta(delta.normalize()) {}

    Vec3f getPos(float deltaMult) const;

    Vec3f origin;
    Vec3f delta;
};
