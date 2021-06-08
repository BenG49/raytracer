#pragma once

#include "../math/vec3.hpp"

class Material
{
public:
    Material(const Vec3f &color);

    Vec3f color;

    // percentage of reflection of specular part of light
    float specular;
    // percentage of reflection of diffuse part of light
    float diffuse;
    float ambient;
    float shininess;
};
