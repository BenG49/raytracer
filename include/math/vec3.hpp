#pragma once

#include <cmath>

template <typename T>
class Vec3
{
public:
    Vec3(T x, T y, T z);
    Vec3(T xyz);
    Vec3(const Vec3<T> &other);

    Vec3<T> operator+(const Vec3<T> &rhs) const;
    Vec3<T> operator-(const Vec3<T> &rhs) const;
    Vec3<T> operator*(const Vec3<T> &rhs) const;
    Vec3<T> operator*(T rhs) const;
    Vec3<T> operator/(T rhs) const;

    Vec3<T> operator+=(const Vec3<T> &rhs);
    Vec3<T> operator-=(const Vec3<T> &rhs);

    T operator[](int index) const;

    T dot(const Vec3<T> &other) const;
    T dist(const Vec3<T> &other) const;
    T magnitude() const;

    Vec3<T> cross(const Vec3<T> &other) const;
    Vec3<T> rotate(float pitch, float yaw) const;
    Vec3<T> normalize() const;

    void print() const;

    T x, y, z;
};

typedef Vec3<float> Vec3f;
typedef Vec3f Color;

const Vec3f ORIG(0);
