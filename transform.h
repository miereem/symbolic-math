//
// Created by yfcni on 12/21/2023.
//

#ifndef SYMBOLIC_TRANSFORM_H
#define SYMBOLIC_TRANSFORM_H

#include <corecrt.h>
#include "structures.h"
struct Context {
    size_t numNames;
    char **names;
    Expression ** definitions;
};
void set(struct Expression* node);
void initContext();
#endif //SYMBOLIC_TRANSFORM_H
