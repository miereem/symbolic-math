#ifndef LLP2_DERIVATIVE_H
#define LLP2_DERIVATIVE_H

#include <stdio.h>
#include <stdlib.h>
#include "../../structureMain.h"


ExpressionNode *derivateExpression(ExpressionNode *expressionNode);

void unaryDerivative(ExpressionNode **expressionNode, ExpressionNode *(*dirative)());

void multiplication(ExpressionNode *expressionNode);

void division(ExpressionNode *expressionNode);

void derivative(ExpressionNode *expressionTree);

#endif //LLP2_DERIVATIVE_H
