#pragma once

#include <vector>
#include <memory>

#include "../math/vec3.hpp"
#include "triangle.hpp"

#include "SFML/Graphics/Color.hpp"

class Light
{
public:
    Light(const Vec3f &pos)
        : pos(pos) {}

    bool inShadow(const Intersection &intersection, const Vec3f &camera, std::vector<std::unique_ptr<Shape>> &shapese) const;

    Vec3f pos;
};
