//
// Created by yfcni on 12/26/2023.
//

#ifndef SYMBOLIC_STRUCTURES_H
#define SYMBOLIC_STRUCTURES_H

#include <stdbool.h>
#include <stdio.h>

//#include <corecrt.h>

enum Hold {
    NONE, ALL, FIRST, REST
};
struct Point {
    double x;
    double y;
} typedef Point;
struct PointArray {
    Point *points;
    int count;
} typedef PointArray;
struct Plots{
    PointArray *plots;
    int count;
};
struct PlotDTO{
    struct Plots plots;
    int width;
    int height;
};
typedef struct Expression {
    char *symbol;
    struct Expression *children;
    int numChildren;
    enum Hold hold;
} Expression;


struct DefinitionArray {
    Expression *definitionArray;
    size_t size;
} typedef DefinitionArray;

struct Context {
    size_t numNames;
    char **names;
    DefinitionArray *definitions;
};

#endif //SYMBOLIC_STRUCTURES_H