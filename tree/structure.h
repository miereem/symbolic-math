#include <stdlib.h>

#ifndef ALGORITHM_STRUCTURE_H
#define ALGORITHM_STRUCTURE_H
typedef enum {
    OPERATOR,
    VARIABLE,
    CONSTANT
} TokenType;

typedef enum {
    ADD,
    SUB,
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


ExpressionNode* createOperandNode();

ExpressionNode* createOperatorNode();

void freeExpressionTree();

ExpressionNode* createExpressionTree();


#endif //ALGORITHM_STRUCTURE_H
