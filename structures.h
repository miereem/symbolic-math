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

typedef struct Expression {
    char *symbol;
    struct Expression *children;
    int numChildren;
    enum Hold hold;
} Expression;



struct DefinitionArray{
    Expression * definitionArray;
    size_t size;
    enum Hold* attrs;
    size_t countOfAttrs;
} typedef DefinitionArray;

struct Context {
    size_t numNames;
    char **names;
    DefinitionArray * definitions;
};

#endif //SYMBOLIC_STRUCTURES_H
