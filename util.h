//
// Created by Home on 22.12.2023.
//

#ifndef SYMBOLIC_UTIL_H
#define SYMBOLIC_UTIL_H


#include "structures.h"

void printTree(Expression *root);

void addChild(Expression *parent, Expression *child);

Expression *createNode(char *symbol);

Expression *copyNode(Expression *node);

#endif //SYMBOLIC_UTIL_H
