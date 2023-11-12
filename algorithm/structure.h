
#ifndef ALGORITHM_STRUCTURE_H
#define ALGORITHM_STRUCTURE_H
typedef enum type{
    EXPRESSION_UNARY,
    EXPRESSION_BINARY,
    LIST
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
    ASIN,
    ACOS,
    ATAN,
    ACTAN,
    POWER,
    LOGARITHM
} OperationType;

typedef struct ExpressionNode{
    TokenType type;
    OperationType operation;
    union {
        double digit;
        char* literal;
    } value;
    struct expression* left;
    struct expression* right;
} ExpressionNode;

#endif //ALGORITHM_STRUCTURE_H
