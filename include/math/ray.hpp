#pragma once

#include "../../src/math/vec3.cpp"

struct Ray
{
    Ray(const Vec3f &origin, const Vec3f &delta)
        : origin(origin), delta(delta) {}

    Vec3f getPos(float deltaMult) const { return origin + delta * deltaMult; }

    Vec3f origin;
    Vec3f delta;
};
