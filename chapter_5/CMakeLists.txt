cmake_minimum_required(VERSION 3.10)

project(ch_5_test)

# 添加test.txt配置文件
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# 添加编译和链接选项 -pthread
add_compile_options(-pthread)

link_libraries(-pthread)

add_executable(output main.cpp )