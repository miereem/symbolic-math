//
// Created by Home on 22.12.2023.
//

#ifndef SYMBOLIC_UTIL_H
#define SYMBOLIC_UTIL_H


#include "structures.h"


void addChild(Expression *parent, Expression *child);

Expression *createNode(char *symbol);
void printExpression(Expression *node);

Expression *copyNode(Expression *node);
void freeExpression(Expression *expr);

#endif //SYMBOLIC_UTIL_H
