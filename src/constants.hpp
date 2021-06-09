#include "../include/math/vec3.hpp"

const int XRES = 640;
const int YRES = 480;

const float XVIEWPLANE = 0.5f;
// keep view plane in same ratio as resolution
const float YVIEWPLANE = (YRES / (float) XRES) * XVIEWPLANE;
const float RAYDX = XVIEWPLANE / XRES;
const float RAYDY = YVIEWPLANE / YRES;

const float VIEWPLANE_XSTART = -XVIEWPLANE/2.0f;
const float VIEWPLANE_YSTART = -YVIEWPLANE/2.0f;

const int MAX_DEPTH = 3;

const Vec3f BACKGROUND(255, 255, 255);
