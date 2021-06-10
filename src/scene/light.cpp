#include "../../include/scene/light.hpp"
#include "../constants.hpp"

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

// https://en.wikipedia.org/wiki/Phong_reflection_model
Color Light::phongLighting(const Intersection &intersection, const Material &mat, const Vec3f &cam, std::vector<std::unique_ptr<Light>> &lights)
{
    float illumination = mat.ambient * AMBIENT;
    Vec3f v = (intersection.hit - cam).normalize();

    for (int i = 0; i < lights.size(); ++i)
    {
        Light *cur = lights[i].get();
        Vec3f l = (cur->pos - intersection.hit).normalize();
        Vec3f r = l.reflect(intersection.norm);

        float diffuse = mat.diffuse * l.dot(intersection.norm) * cur->diffuse;

        // float lambda = 1 - r.dot(v);
        float lambda = r.cross(v).dot(r.cross(v)) / 2.0f;
        float beta = mat.shininess / (float)GAMMA;
        float specular = mat.specular * std::pow(std::max(0.0f, 1-beta*lambda), GAMMA) * cur->specular;
        // float specular = mat.specular * std::pow(r.dot(v), mat.shininess) * cur->specular;

        illumination += diffuse + specular;
    }

    return mat.color * illumination;
}
