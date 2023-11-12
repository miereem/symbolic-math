#include <stdlib.h>

#ifndef ALGORITHM_STRUCTURE_H
#define ALGORITHM_STRUCTURE_H
typedef enum {
        OPERATOR,
        VARIABLE,
        CONSTANT
} TokenType;

typedef enum {
    PLUS,
    MINUS,
    MUL,
    DIV,
    SIN,
    COS,
    TAN,
    CTAN,
    ASIN,
    ACOS,
    ATAN,
    ACTAN,
    POWER,
    LOG,
    NEG
} OperatorType;

typedef struct ExpressionNode {
    TokenType type;
    union {
        OperatorType operatorType;
        char variable;
        double constant;
    } value;

    struct ExpressionNode* left;
    struct ExpressionNode* right;
} ExpressionNode;

ExpressionNode* createOperandNode(TokenType type, double value) {
    ExpressionNode* node = (ExpressionNode*)malloc(sizeof(ExpressionNode));
    if (node == NULL) {

        exit(EXIT_FAILURE);
    }

    node->type = type;
    if (type == CONSTANT) {
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


#endif //ALGORITHM_STRUCTURE_H
