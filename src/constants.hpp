#include "../include/math/vec3.hpp"

const int XRES = 640;
const int YRES = 480;

const float XVIEWPLANE = 1.0f;
// keep view plane in same ratio as resolution
const float YVIEWPLANE = (YRES / (float) XRES) * XVIEWPLANE;
const float RAYDX = XVIEWPLANE / XRES;
const float RAYDY = YVIEWPLANE / YRES;

const float VIEWPLANE_XSTART = -XVIEWPLANE/2.0f;
const float VIEWPLANE_YSTART = -YVIEWPLANE/2.0f;

const int MAX_DEPTH = 3;

// FLOOR

const float FLOOR_HEIGHT = 0;

const int SQ_SIZE = 1;
const int SQ_SIZE2 = SQ_SIZE * 2;

const int FLOOR_AREA = 10;

// LIGHT

const float AMBIENT = 0.2f;
const int GAMMA = 4;

// COLORS

const Vec3f BACKGROUND(5, 185, 250);
const Vec3f GRAY(100);
