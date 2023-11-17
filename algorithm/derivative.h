#ifndef LLP2_DERIVATIVE_H
#define LLP2_DERIVATIVE_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"


ExpressionNode *derivateExpression(ExpressionNode *expressionNode);

ExpressionNode *createOperation(OperationType operationType);

void unaryDerivative(ExpressionNode **expressionNode, ExpressionNode *(*dirative)());

void multiplication(ExpressionNode *expressionNode);

void division(ExpressionNode *expressionNode);

void derivative(ExpressionNode *expressionTree);

#endif //LLP2_DERIVATIVE_H
