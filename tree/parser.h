#include <stdio.h>
#include <stdlib.h>
#include "../algorithm/structure.h"

int parseNumber(const char **expr);
char parseOperator(const char **expr);
struct ExpressionNode* parseExpression(const char **expr, int minPrecedence);
struct ExpressionNode* parsePrimary(const char **expr);

// Определяем приоритет
int getPrecedence(char op);
// строим число из его цифр ( типо распрастранненый метод)
int parseNumber();

// Парсим оператора
char parseOperator();

char parseVariable();


// Создаем ноду
struct ExpressionNode* createNode(TokenType type, int operand, char variable, char op, OperationType operationType, struct ExpressionNode *left, struct ExpressionNode *right);
void printInfix(struct ExpressionNode *node);
// Parse a primary expression (number or expression in parentheses)
struct ExpressionNode* parsePrimary();

// выражения
struct ExpressionNode* parseExpression();

//выводим приорите нод в нотации
void printPrefix();
//
//int main() {
//    const char *input = "((3+c)*a)-7";
//    struct ExpressionNode *ast = parseExpression(&input, 0);
//
//    printf("Postfix Notation: ");
//    printPostfix(ast);
//    printf("\n");
//
//
//    // освобождаем память для нод
//    free(ast);
//
//    return 0;
//}