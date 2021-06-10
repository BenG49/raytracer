#pragma once

#include "../math/vec3.hpp"

struct Intersection
{
    // creates missed intersection
    Intersection()
        : intersected(false)
        , hit(ORIG)
        , norm(ORIG) {}
    
    Intersection(bool intersected, const Vec3f &hit, const Vec3f &norm, float t0)
        : intersected(intersected)
        , hit(hit)
        , norm(norm.normalize())
        , t0(t0) {}
    
    bool intersected;

    Vec3f hit;
    Vec3f norm;

    float t0;
};
