#include "structure.h"
#include <math.h>
#include "derivetive_operations.h"

ExpressionNode *sin_d(ExpressionNode *expressionNode) {
    expressionNode->operationType = COS;
    return expressionNode;
}

ExpressionNode *cos_d(ExpressionNode *expressionNode) {
    ExpressionNode *neg = createOperation(NEGATIVE);
    neg->left = expressionNode;
    expressionNode->operationType = SIN;
    return neg;
}
ExpressionNode *pow_d(ExpressionNode *expressionNode) {
    ExpressionNode *mult = createOperation(MULTIPLICATION);
    ExpressionNode * minus = createOperation(MINUS);
    mult->left = expressionNode->right;

    mult->right = expressionNode;
    minus->left=expressionNode->right;
    minus->right= createConst(1);

    expressionNode->right=minus;

    return mult;
}

ExpressionNode *neg_d(ExpressionNode *expressionNode) {
    return expressionNode;
}
ExpressionNode *log_d(ExpressionNode *expressionNode) {
    ExpressionNode *division = createOperation(DIVISION);
    division->left = createConst(1);

    ExpressionNode *mult = createOperation(MULTIPLICATION);
    mult->left= expressionNode->right;

    expressionNode->left->type=CONSTANT;
    expressionNode->left->operand=exp(1);
    mult->right=expressionNode;

    return division;
}
ExpressionNode *tan_d(ExpressionNode *expressionNode) {
    ExpressionNode *division = createOperation(DIVISION);
    division->left = createConst(1);

    expressionNode->operationType=COS;

    ExpressionNode *mult = createOperation(POWER);
    mult->left= expressionNode;
    mult->right= createConst(2);

    return division;
}
ExpressionNode *ctan_d(ExpressionNode *expressionNode) {
    ExpressionNode *division = createOperation(DIVISION);
    division->left = createConst(1);

    expressionNode->operationType=SIN;

    ExpressionNode *mult = createOperation(POWER);
    mult->left= expressionNode;
    mult->right= createConst(2);

    return division;
}



