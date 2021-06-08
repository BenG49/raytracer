#pragma once

#include "shape.hpp"
#include "../math/vec3.hpp"

class Sphere : public Shape
{
public:
    Sphere(const Vec3f &center, float radius, const Material& m);

    Intersection getIntersection(const Ray &ray) const override;
    Material getMat() const override;

private:
    Vec3f center;
    Material m;
    float radius, r2;
};
