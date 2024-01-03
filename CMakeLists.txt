cmake_minimum_required(VERSION 3.24)

project(symbolic C)

set(CMAKE_C_STANDARD 11)

add_executable(symbolic main.c transformer.c evaluator.c transformer.h structures.h parser.h evaluator.h parser.c solver.h solver.c)
#structures.c parser.c
