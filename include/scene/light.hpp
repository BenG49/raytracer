#pragma once

#include "shape.hpp"
#include <memory>
#include <vector>

class Light
{
public:
    Light(const Vec3f &pos, float diffuse, float specular)
        : pos(pos)
        , diffuse(diffuse)
        , specular(specular) {}
    
    bool inShadow(const Intersection &intersection, const Vec3f &camera, std::vector<std::unique_ptr<Shape>> &shapes) const;
    static Color phongLighting(const Intersection &intersection, const Material &mat, const Vec3f &cam, std::vector<std::unique_ptr<Light>> &lights);

    Vec3f pos;

    float diffuse;
    float specular;
};
