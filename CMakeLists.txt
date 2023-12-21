cmake_minimum_required(VERSION 3.24)
project(symbolic C)

set(CMAKE_C_STANDARD 11)

add_executable(symbolic main.c
        transform.c
        transform.h
        parser.c
        structures.c
        evaluate.c
        evaluate.h)
#structures.c parser.c
