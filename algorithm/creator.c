#include "creator.h"
#include <stdlib.h>
ExpressionNode *createOperation(OperationType operationType) {
    ExpressionNode *expressionNode = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    expressionNode->type = OPERATOR;
    expressionNode->value.operationType = operationType;
    return expressionNode;
}

ExpressionNode *createConst(double constant) {
    ExpressionNode *expressionNode = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    expressionNode->type = CONSTANT;
    expressionNode->value.constant = constant;
    return expressionNode;
}
ExpressionNode *makeCopy(ExpressionNode * expressionNode) {
    ExpressionNode *newExpressionNode = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    *newExpressionNode=*expressionNode;
    return newExpressionNode;
}