
#ifndef SYMBOLIC_TRANSFORM_H
#define SYMBOLIC_TRANSFORM_H
#include "util.h"

void printContext();

void set(struct Expression *node, bool isDelayed);

void initContext();

int isInContext(char *name);

Expression *evaluate(Expression *expression);

Expression *compareAndAddToContext(Expression *inputTree, Expression *setTree);

Expression *evaluateExpression(Expression *node);
void addAttrs(char* name, enum Hold attr);

#endif //SYMBOLIC_TRANSFORM_H