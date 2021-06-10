#include "../../include/scene/sphere.hpp"

Sphere::Sphere(const Vec3f &center, float radius, const Material &mat)
    : center(center)
    , radius(radius)
    , r2(radius * radius)
    , mat(mat) {}

Intersection Sphere::getIntersection(const Ray &ray) const
{
    Vec3f l = center - ray.origin;
    float tca = l.dot(ray.delta);
    float d2 = l.dot(l) - tca * tca;
    if (d2 > r2) return Intersection();
    float thc = std::sqrt(r2 - d2);
    // delta mult for first intersection
    float t0 = tca - thc;
    // delta mult for second intersection
    float t1 = tca + thc;

    // if entrance is farther than exit
    if (t0 > t1) std::swap(t0, t1);

    // prevents self intersection
    if (t0 < EPSILON && t1 < EPSILON) return Intersection();

    Vec3f hit = ray.getPos(t0);
    return Intersection(true, hit, hit - center);
}

Material Sphere::getMat() const { return mat; }
