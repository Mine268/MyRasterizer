cmake_minimum_required(VERSION 3.24)

project(MyRasterizer2)

# 需要使用 Eigen 库
set(Eigen3_DIR "C:\\Eigen3\\share\\eigen3\\cmake")
find_package(Eigen3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIRS})

# 对象文件加载类
add_library(obj_loader src/OBJ_loader.cpp)

# 三角形类 mesh
add_library(mesh src/mesh.cpp)

# 工具库
add_library(utils src/utils.cpp)
target_link_libraries(utils mesh obj_loader)

# 生成目标
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} utils mesh)
