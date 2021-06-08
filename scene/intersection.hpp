#pragma once

#include "../math/vec3.hpp"

// shamelessly stolen from myles
struct Intersection
{
    bool intersected;
    Vec3f hit;
    Vec3f normal;
};

const Intersection MISSED = { false, NULLVEC, NULLVEC };
