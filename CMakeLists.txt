cmake_minimum_required(VERSION 3.14)
project(PSO)

set(CMAKE_CXX_STANDARD 14)

add_executable(PSO main.cpp Particle.cpp Particle.h PSO.cpp PSO.h Statistic.cpp Statistic.h)