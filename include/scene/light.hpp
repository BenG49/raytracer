#pragma once

#include "shape.hpp"
#include <memory>
#include <vector>

class Light
{
public:
    Light(const Vec3f &pos, const Color &diffuse, const Color &specular)
        : pos(pos)
        , diffuse(diffuse)
        , specular(specular) {}
    
    bool inShadow(const Intersection &intersection, const Vec3f &camera, std::vector<std::unique_ptr<Shape>> &shapes) const;

    Vec3f pos;

    Color diffuse;
    Color specular;
};
