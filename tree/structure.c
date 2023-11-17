#include <stdlib.h>
#include <stdio.h>
#include "structure.h"

ExpressionNode* createOperandNode(TokenType type, double value) {
    ExpressionNode* node = (ExpressionNode*)malloc(sizeof(ExpressionNode));
    if (node == NULL) {

        exit(EXIT_FAILURE);
    }

    node->type = type;
    if (type == NUMBER) {
        node->value.constant = value;
    } else  if (type == VARIABLE) {
        node->value.variable = value;
    }

    node->left = NULL;
    node->right = NULL;

    return node;
}

ExpressionNode* createOperatorNode(OperatorType operatorType) {
    ExpressionNode* node = (ExpressionNode*)malloc(sizeof(ExpressionNode));
    if (node == NULL) {

        exit(EXIT_FAILURE);
    }

    node->type = OPERATOR;
    node->value.operatorType = operatorType;
    node->left = NULL;
    node->right = NULL;

    return node;
}


void freeExpressionTree(ExpressionNode* root) {
    if (root == NULL) {
        return;
    }

    freeExpressionTree(root->left);
    freeExpressionTree(root->right);
    free(root);
}

//
//ExpressionNode* createExpressionTree(ExpressionNode expressionNode) {
//    if (expressionNode.type == OPERATOR) {
//
//        ExpressionNode* operatorNode = createOperatorNode(());
//    } else if (expressionNode.type == VARIABLE) {
//        ExpressionNode* operand1 = createOperandNode(NUMBER, 3.0);
//    } else if (expressionNode.type == NUMBER) {
//
//    } else {
//        fprintf(stderr, "Error: Unrecognized token\n");
//        exit(EXIT_FAILURE);
//    }
//    ExpressionNode* operatorNode = createOperatorNode(ADD);
//
//    ExpressionNode* operand1 = createOperandNode(NUMBER, 3.0);
//    if (operand2->type == OPERATOR) {
//        ExpressionNode* operand2 = createExpressionTree(operator);
//    } else {
//        ExpressionNode* operand2 = createOperandNode(NUMBER, 4.0);
//    }
//
//
//    operatorNode->left = operand1;
//    operatorNode->right = operand2;
//
//    return operatorNode;
//}




