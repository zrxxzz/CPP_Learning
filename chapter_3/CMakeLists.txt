cmake_minimum_required(VERSION 3.10)

project(second_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(output main.cpp second_class.cpp test_static_class.cpp)