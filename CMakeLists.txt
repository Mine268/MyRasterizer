cmake_minimum_required(VERSION 3.22)
project(MyRasterizer)

set(CMAKE_CXX_STANDARD 20)


add_library(mr_tookit mr_tookit.cpp)

add_library(ObjectLoader ObjectLoader.cpp)

add_library(Vector Vector.cpp)
add_library(Vertex Vertex.cpp)
add_library(Triangle Triangle.cpp)
add_library(TriangleMesh TriangleMesh.cpp)

add_library(MeshObject MeshObject.cpp)

add_library(Matrix Matrix.cpp)
add_library(ResidualMat ResidualMat.cpp)

add_library(RGBRasterizedImage RGBRasterizedImage.cpp)

add_library(Camera Camera.cpp Camera.h)

add_executable(MyRasterizer main.cpp
        ObjectLoader Vertex Triangle Vector mr_tookit TriangleMesh Matrix ResidualMat MeshObject RGBRasterizedImage
        Camera)
