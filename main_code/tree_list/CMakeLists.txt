cmake_minimum_required(VERSION 3.21)
project(tree_list C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(tree_list
        main.c
        tree_list.c
        tree_list.h)
