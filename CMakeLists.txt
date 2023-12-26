cmake_minimum_required(VERSION 3.24)

project(symbolic C)

set(CMAKE_C_STANDARD 11)

add_executable(
        evaluate.c
        evaluate.h
        evaluator.c
        evaluator.h
        main.c
        parser.c
        parser.h
        structures.h
        util.h
        util.c
        transformer.c
        transformer.h
)

