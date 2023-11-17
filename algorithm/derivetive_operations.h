#ifndef LLP2_DERIVETIVE_OPERATIONS_H
#define LLP2_DERIVETIVE_OPERATIONS_H
#include "structure.h"
ExpressionNode * sin_d(ExpressionNode* expressionNode);
ExpressionNode *cos_d(ExpressionNode *expressionNode);
ExpressionNode *createOperation(OperationType operationType);
ExpressionNode *pow_d(ExpressionNode *expressionNode);
ExpressionNode *log_d(ExpressionNode *expressionNode);
ExpressionNode *tan_d(ExpressionNode *expressionNode);
ExpressionNode *ctan_d(ExpressionNode *expressionNode);
ExpressionNode *neg_d(ExpressionNode *expressionNode);

ExpressionNode *createConst(double constant);
#endif //LLP2_DERIVETIVE_OPERATIONS_H
