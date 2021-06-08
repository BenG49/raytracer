#pragma once

const int RES_X = 640;
const int RES_Y = 480;

const float HALF_RES_X = RES_X / 2.0f;
const float HALF_RES_Y = RES_Y / 2.0f;

const float VIEW_PLANE_X_SIZE = 0.5;
const float VIEW_PLANE_Y_SIZE = 0.375;
const float RAY_DX = VIEW_PLANE_X_SIZE / RES_X;
const float RAY_DY = VIEW_PLANE_Y_SIZE / RES_Y;

const Vec3f BACKGROUND = Vec3f(255, 255, 255);
