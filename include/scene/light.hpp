#pragma once

#include "shape.hpp"
#include <memory>
#include <vector>

class Light
{
public:
    Light(const Vec3f &pos, const Vec3f &brightness)
        : pos(pos)
        , brightness(brightness) {}
    
    bool inShadow(const Intersection &intersection, const Vec3f &camera, std::vector<std::unique_ptr<Shape>> &shapes) const;

    Vec3f pos;
    Vec3f brightness;
};
