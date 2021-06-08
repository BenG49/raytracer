#pragma once

#include "../math/ray.hpp"
#include "intersection.hpp"
#include "material.hpp"
#include "SFML/Graphics/Color.hpp"

class Shape
{
public:
    virtual Intersection getIntersection(const Ray &ray) const = 0;
    virtual Material getMat() const = 0;
};
