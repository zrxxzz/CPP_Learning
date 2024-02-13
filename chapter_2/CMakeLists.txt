# 设置CMake的最小版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(my_project)

# 设置标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(output extern.cpp my_class.cpp)
