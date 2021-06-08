#!/usr/bin/env sh


g++ -c src/math/vec3.cpp src/scene/sphere.cpp src/scene/light.cpp src/main.cpp

g++ *.o -O3 -pthread -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

mv *.o build