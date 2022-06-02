cmake_minimum_required(VERSION 3.15)
project(render_my_way C)

set(CMAKE_C_STANDARD 99)

add_executable(render_my_way main.c line.c defines.h object-file.c triangle.c helpers.c)