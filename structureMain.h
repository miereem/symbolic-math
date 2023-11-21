//
// Created by Home on 17.11.2023.
//

#ifndef UNTITLED1_STRUCTUREMAIN_H
#define UNTITLED1_STRUCTUREMAIN_H
typedef enum type{
    OPERATOR,
    NUMBER,
    VARIABLE,
    FUNCTION
} TokenType;
typedef enum operation{
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    SIN,
    COS,
    TAN,
    CTAN,
    POWER,
    LOGARITHM,
    NEGATIVE
} OperationType;

typedef struct ExpressionNode{
    TokenType type;
    union {
        double operand;
        char variable;
        char op;
        char* function
    };
    OperationType operationType;
    struct ExpressionNode* left;
    struct ExpressionNode* right;
} ExpressionNode;
#endif //UNTITLED1_STRUCTUREMAIN_H
