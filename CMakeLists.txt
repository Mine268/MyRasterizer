cmake_minimum_required(VERSION 3.23)

project(MyRasterizer2)

# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CXX17
set(CXX_STANDARD 17)

# 需要使用 Eigen 库
set(Eigen3_DIR "C:\\Eigen3\\share\\eigen3\\cmake")
find_package(Eigen3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIRS})

# 图片
add_library(stb_image_write src/stb_image_write.cpp)
add_library(image src/image.cpp)
target_link_libraries(image stb_image_write)

# 对象文件加载类
add_library(obj_loader src/OBJ_loader.cpp)

# 三角形类 mesh
add_library(mesh src/mesh.cpp)

# 工具库
add_library(utils src/utils.cpp)
target_link_libraries(utils mesh obj_loader)

# 世界对象类
add_library(world_object src/world_object.cpp)

# 平行光
add_library(parallel_light src/parallel_light.cpp)

# 相机类
add_library(camera src/camera.cpp)
target_link_libraries(camera utils)

# 场景类
add_library(scene src/scene.cpp)
target_link_libraries(scene parallel_light camera world_object image)

# 生成目标
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} utils mesh obj_loader world_object scene)
