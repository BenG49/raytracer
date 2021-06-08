#!/usr/bin/env sh

g++ -c src/math/vec3.cpp src/math/plane.cpp src/math/ray.cpp
g++ -c src/scene/material.cpp src/scene/triangle.cpp src/scene/sphere.cpp src/scene/light.cpp
g++ -c src/main.cpp

g++ *.o -O3 -pthread -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

mv *.o build