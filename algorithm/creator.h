#ifndef LLP2_CREATOR_H
#define LLP2_CREATOR_H

#include "../structureMain.h"

ExpressionNode *createOperation(OperationType operationType);

ExpressionNode *makeCopy(ExpressionNode *expressionNode);

ExpressionNode *createConst(double constant);

#endif //LLP2_CREATOR_H
