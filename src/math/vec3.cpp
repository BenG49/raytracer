#include "../../include/math/vec3.hpp"

#include <iostream>

template <typename T>
Vec3<T>::Vec3(T x, T y, T z)
    : x(x), y(y), z(z) {}

template <typename T>
Vec3<T>::Vec3(T xyz)
    : Vec3(xyz, xyz, xyz) {}

template <typename T>
Vec3<T>::Vec3(const Vec3<T> &other)
    : Vec3(other.x, other.y, other.z) {}

template <typename T>
Vec3<T> Vec3<T>::operator+(const Vec3<T> &rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
template <typename T>
Vec3<T> Vec3<T>::operator-(const Vec3<T> &rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
template <typename T>
Vec3<T> Vec3<T>::operator*(const Vec3<T> &rhs) const { return Vec3f( x * rhs.x, y * rhs.y, z * rhs.z); }
template <typename T>
Vec3<T> Vec3<T>::operator*(T rhs) const { return Vec3(x * rhs, y * rhs, z * rhs); }
template <typename T>
Vec3<T> Vec3<T>::operator/(T rhs) const { return Vec3(x / rhs, y / rhs, z / rhs); }

template <typename T>
Vec3<T> Vec3<T>::operator+=(const Vec3<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
};
template <typename T>
Vec3<T> Vec3<T>::operator-=(const Vec3<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
};

template <typename T>
T Vec3<T>::operator[](int index) const
{
    switch (index) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default:
            perror("Vector out of bounds!");
            throw -1;
    }
}

template<typename T>
T Vec3<T>::dot(const Vec3<T> &other) const
{ return x * other.x + y * other.y + z * other.z; }

template<typename T>
T Vec3<T>::dist(const Vec3<T> &other) const
{
    return sqrt(
        pow(x - other.x, 2) +
        pow(y - other.y, 2) +
        pow(z - other.z, 2)
    );
}

template<typename T>
T Vec3<T>::magnitude() const
{
    return sqrt(x*x + y*y + z*z);
}

template<typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T> &other) const
{
    return Vec3<T>(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x);
}

// takes in radians
template<typename T>
Vec3<T> Vec3<T>::rotate(float pitch, float yaw) const
{
    // rotation around y axis
    T ySin = sin(yaw);
    T yCos = cos(yaw);
    Vec3<T> out(
        x * yCos + z * ySin,
        y,
        -x * ySin + z * yCos
    );

    // rotation around x axis
    T pSin = sin(pitch);
    T pCos = cos(pitch);
    return Vec3<T>(
        out.x,
        out.y * pCos - out.z * pSin,
        out.y * pSin + out.z * pCos
    );
}

template<typename T>
Vec3<T> Vec3<T>::normalize() const
{
    float mag = this->magnitude();
    if (mag > 0)
        return (*this)/mag;
    
    return *this;
}

template<typename T>
void Vec3<T>::print() const
{
    std::cout << '(' << x << ", " << y << ", " << z << ')' << std::endl;
}

