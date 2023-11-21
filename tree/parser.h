#include <stdio.h>
#include <stdlib.h>


//int parseNumber(const char **expr);
//char parseOperator(const char **expr);
struct ExpressionNode* parseExpression(const char **expr, int minPrecedence);
struct ExpressionNode* parsePrimary(const char **expr);

//int getPrecedence(char op);
//int parseNumber();

//char parseOperator();
//char parseVariable();
//
//
//struct ExpressionNode* createNode(TokenType type, int operand, char variable, char op, OperationType operationType, struct ExpressionNode *left, struct ExpressionNode *right);
void printInfix(struct ExpressionNode *node);

//struct ExpressionNode* parsePrimary();
//
//struct ExpressionNode* parseExpression();
//
//void printPrefix();
