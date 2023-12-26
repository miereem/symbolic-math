//
// Created by yfcni on 12/21/2023.
//

#ifndef SYMBOLIC_TRANSFORM_H
#define SYMBOLIC_TRANSFORM_H

#include <corecrt.h>
#include "structures.h"
struct DefinitionArray{
    Expression * definitionArray;
    size_t size;
} typedef DefinitionArray;
struct Context {
    size_t numNames;
    char **names;
    DefinitionArray * definitions;
};
void set(struct Expression* node);
void initContext();
#endif //SYMBOLIC_TRANSFORM_H
