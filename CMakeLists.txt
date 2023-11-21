#cmake_minimum_required(VERSION 3.26)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled1 main.c
        tree/parser.c
        tree/parser.h structureMain.h
        algorithm/integral/integral_operation.c
        algorithm/integral/integral.h
        algorithm/creator.c
        algorithm/derivative/derivetive_operation.c
        algorithm/integral/integral.c)
