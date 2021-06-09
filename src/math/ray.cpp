#include "../../include/math/ray.hpp"

Vec3f Ray::getPos(float deltaMult) const { return origin + delta * deltaMult; }

Ray Ray::reflect(const Intersection &intr) const
{
    Vec3f newDelta = intr.norm - delta * (2 * intr.norm.dot(delta));

    return Ray(intr.hit, newDelta);
}
