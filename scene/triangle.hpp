#pragma once

#include "shape.hpp"
#include "../math/vec3.hpp"

class Triangle : public Shape
{
public:
    Triangle(const Vec3f &a, const Vec3f &b, const Vec3f &c, const Material &color);

    Intersection getIntersection(const Ray &ray) const override;
    Material getMat() const override;

    Plane plane;

private:
    Vec3f a, b, c;
    Material color;

    bool axisWithinBounds(const Vec3f &pIntersect, int i) const;
    bool pointsSameSideLine(Vec3f a, Vec3f b, Vec3f lA, Vec3f lB) const;

    float min(float x, float y, float z) const;
    float max(float x, float y, float z) const;
};
