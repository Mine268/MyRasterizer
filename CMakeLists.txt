cmake_minimum_required(VERSION 3.22)
project(MyRasterizer)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyRasterizer main.cpp ObjectLoader.cpp ObjectLoader.h Vertex.cpp Vertex.h Triangle.cpp Triangle.h Vector.cpp Vector.h)
