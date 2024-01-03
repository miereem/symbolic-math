
#ifndef SYMBOLIC_TRANSFORM_H
#define SYMBOLIC_TRANSFORM_H

//#include <corecrt.h>
#include "structures.h"
#include <stdio.h>
struct DefinitionArray {
    Expression *definitionArray;
    size_t size;
} typedef DefinitionArray;
struct Context {
    size_t numNames;
    char **names;
    DefinitionArray *definitions;
};

void printContext();

void set(struct Expression *node);

void initContext();

int isInContext(char *name);

Expression *evaluate(Expression *expression);

Expression *compareAndAddToContext(Expression *inputTree, Expression *setTree);

Expression *evaluateExpression(Expression *node);
void printExpression(Expression *node);

#endif //SYMBOLIC_TRANSFORM_H