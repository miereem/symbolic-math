#include "creator.h"
#include <stdlib.h>
ExpressionNode *createOperation(OperationType operationType) {
    ExpressionNode *expressionNode = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    expressionNode->type = OPERATOR;
    expressionNode->operationType = operationType;
    return expressionNode;
}

ExpressionNode *createConst(double constant) {
    ExpressionNode *expressionNode = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    expressionNode->type = NUMBER;
    expressionNode->operand = constant;
    return expressionNode;
}
ExpressionNode *makeCopy(ExpressionNode * expressionNode) {
    ExpressionNode *newExpressionNode = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    *newExpressionNode=*expressionNode;
    switch (expressionNode->operationType) {

        case PLUS|MINUS|MULTIPLICATION|DIVISION|POWER:
            newExpressionNode->left= makeCopy(newExpressionNode->left);
            newExpressionNode->right= makeCopy(newExpressionNode->right);
            break;
        case SIN|COS|TAN|CTAN|POWER|LOGARITHM|NUMBER:
            newExpressionNode->left= makeCopy(newExpressionNode->left);
            break;
    }
    return newExpressionNode;
}