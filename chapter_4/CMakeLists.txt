cmake_minimum_required(VERSION 3.10)

project(ch_4_test)

# 添加test.txt配置文件
configure_file(test.txt ${CMAKE_BINARY_DIR}/test.txt COPYONLY)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(output main.cpp second_class.cpp)