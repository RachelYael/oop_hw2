cmake_minimum_required(VERSION 3.21)
project(hw2)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw2 main.cpp Vehicle.cpp Vehicle.h Bus.cpp Bus.h Tram.cpp Tram.h Sprinter.cpp Sprinter.h Rail.cpp Rail.h Simulation.cpp Simulation.h Graph.cpp Graph.h GraphHelper.cpp GraphHelper.h)
