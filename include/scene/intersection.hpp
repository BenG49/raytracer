#pragma once

#include "../math/vec3.hpp"

struct Intersection
{
    // creates missed intersection
    Intersection()
        : intersected(false)
        , hit(NULLVEC)
        , norm(NULLVEC) {}
    
    Intersection(bool intersected, const Vec3f &hit, const Vec3f &norm)
        : intersected(intersected)
        , hit(hit)
        , norm(norm) {}
    
    bool intersected;

    Vec3f hit;
    Vec3f norm;
};
