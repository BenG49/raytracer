#include "../../scene/light.hpp"

#include <iostream>

bool Light::inShadow(const Intersection &intersection, const Vec3f &camera, std::vector<std::unique_ptr<Shape>> &shapes) const
{
    Ray rayToLight(intersection.hit, pos - intersection.hit);

    for (int i = 0; i < shapes.size(); ++i)
    {
        if (shapes[i].get()->getIntersection(rayToLight).intersected)
            return true;
    }

    return false;
}
