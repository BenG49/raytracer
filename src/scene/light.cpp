#include "../../include/scene/light.hpp"

bool Light::inShadow(const Intersection &intersection, const Vec3f &camera, std::vector<std::unique_ptr<Shape>> &shapes) const
{
    Ray toLight(intersection.hit, pos - intersection.hit);

    for (int i = 0; i < shapes.size(); ++i)
    {
        if (shapes[i].get()->getIntersection(toLight).intersected)
            return true;
    }

    return false;
}
