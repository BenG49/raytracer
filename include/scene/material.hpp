#pragma once

#include "../math/vec3.hpp"

struct Material
{
    // normal material
    Material(const Vec3f &color, float diffuse, float specular, float shininess, float ambient)
        : color(color)
        , reflective(false)
        , diffuse(diffuse)
        , specular(specular)
        , shininess(shininess)
        , ambient(ambient) {}

    // reflective material
    Material()
        : color(ORIG)
        , reflective(true) {}

    Color color;
    bool reflective;

    float diffuse;
    float specular;
    float shininess;
    float ambient;
};
