#ifndef ALGORITHM_STRUCTURE_H
#define ALGORITHM_STRUCTURE_H
typedef enum type{
    OPERATOR,
    CONSTANT,
    VARIABLE
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
        OperationType operationType;
        double constant;
        char variable;
    } value;
    struct ExpressionNode* left;
    struct ExpressionNode* right;
} ExpressionNode;

#endif //ALGORITHM_STRUCTURE_H
