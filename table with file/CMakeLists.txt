cmake_minimum_required(VERSION 3.16)
project(3_file C)

set(CMAKE_C_STANDARD 99)

add_executable(3_file main.c table.c table.h)
