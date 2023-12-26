//
// Created by yfcni on 12/26/2023.
//

#ifndef SYMBOLIC_STRUCTURES_H
#define SYMBOLIC_STRUCTURES_H
#include <stdbool.h>
#include <corecrt.h>

typedef struct Expression {
    char *symbol;
    struct Expression *children;
    int numChildren;
    bool isDelayed;
} Expression;

enum Hold{
    ALL, FIRST, REST
};
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
