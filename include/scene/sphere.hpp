#pragma once

#include "shape.hpp"

class Sphere : public Shape
{
public:
    Sphere(const Vec3f &center, float radius, const Material &mat);

    Intersection getIntersection(const Ray &ray) const override;
    Material getMat() const override;

    Vec3f center;
    float radius, r2;
    Material mat;

private:
    const float EPSILON = 0.001f;
};
