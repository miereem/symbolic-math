#include <stdio.h>
#include "algorithm//derivative.c"

int main() {
    printf("Hello, World!\n");
    ExpressionNode *expressionNode = (ExpressionNode *) malloc(sizeof(ExpressionNode));

    expressionNode->type = OPERATOR;
    expressionNode->value.operationType = PLUS;


    ExpressionNode *expressionNodeL = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    expressionNodeL->type = CONSTANT;
    expressionNodeL->value.constant = 8;

    ExpressionNode *expressionNodeLL = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    expressionNodeLL->type = VARIABLE;
    expressionNodeLL->value.variable = 'a';

    ExpressionNode *expressionNodeR = (ExpressionNode *) malloc(sizeof(ExpressionNode));

    expressionNodeR->type = OPERATOR;
    expressionNodeR->value.operationType = SIN;
    expressionNodeR->left = expressionNodeLL;

    expressionNode->left=expressionNodeL;
    expressionNode->right=expressionNodeR;


    derivative(expressionNode);
//    printf(expressionNode->right.)
    return 0;
}
