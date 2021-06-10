#include "../../include/math/ray.hpp"

Vec3f Ray::getPos(float deltaMult) const { return origin + delta * deltaMult; }
