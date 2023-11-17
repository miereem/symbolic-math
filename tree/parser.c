#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "../algorithm/structure.h"


typedef struct ExpressionNode ExpressionNode;

// Определяем приоритет
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// строим число из его цифр ( типо распрастранненый метод)
int parseNumber(const char **expr) {
    int result = 0;
    while (**expr >= '0' && **expr <= '9') {
        result = result * 10 + (**expr - '0');
        (*expr)++;
    }
    return result;
}


OperationType defineOperationType(const char *name);

struct ExpressionNode *createFunctionNode(const char *functionName) {
    printf("%c ", *functionName);

    int len = strlen(functionName);
    struct ExpressionNode *node = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }

    node->type = FUNCTION;
    node->function = strdup(functionName);
    node->operationType = defineOperationType(functionName);
    node->left = NULL;
    node->right = NULL;


    return node;
}

OperationType defineSimpleOperationType(const char name) {
    if (name == '+') {
        return PLUS;
    } else if (name == '-') {
        return MINUS;
    } else if (name == '*') {
        return MULTIPLICATION;
    } else if (name == '/') {
        return DIVISION;
    };
}

OperationType defineOperationType(const char *name) {
    if (!strcmp(name, "sin")) {
        return SIN;
    } else if (!strcmp(name, "cos")) {
        return COS;
    } else if (!strcmp(name, "pow")) {
        return POWER;
    } else if (!strcmp(name, "tan")) {
        return TAN;
    } else if (!strcmp(name, "ctan")) {
        return CTAN;
    } else if (!strcmp(name, "log")) {
        return LOGARITHM;
    }

    return POWER;
}

struct ExpressionNode *parseFunction(const char **expr) {
    printf("%c ", **expr);
    char functionName[50];
    sscanf(*expr, "%49[^ (]", functionName); // Read until the first space or opening parenthesis
    *expr += strlen(functionName);


    ExpressionNode *functionNode = createFunctionNode(functionName);

    if (**expr == '(') {
        (*expr)++;

        functionNode->left = parsePrimary(expr);

        if (**expr == ',') {
            (*expr)++;
        }
        printf("%s ", *expr);
        functionNode->right = parsePrimary(expr);      //const char *input = "7+sin(cos(x)-7)";


        if (**expr == ')') {
            (*expr)++;
        } else {
            printf("%c ", **expr);
            fprintf(stderr, "Error: Mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }
    }

    return functionNode;
}


// Парсим оператора
char parseOperator(const char **expr) {
    char op = **expr;
    (*expr)++;
    return op;
}

char parseVariable(const char **expr) {
    char var = **expr;
    (*expr)++;
    return var;
}


// Создаем ноду

struct ExpressionNode *createNode(TokenType type, int operand, char variable, char op, OperationType operationType,
                                  struct ExpressionNode *left,
                                  struct ExpressionNode *right) {
    struct ExpressionNode *node = (struct ExpressionNode *) malloc(sizeof(struct ExpressionNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failure\n");
        exit(EXIT_FAILURE);
    }

    node->type = type;
    if (type == NUMBER) {
        node->operand = operand;
    } else if (type == VARIABLE) {
        node->variable = variable;
    } else if (type == OPERATOR) {
        node->op = op;
        node->operationType = defineSimpleOperationType(op);
    }
    node->left = left;
    node->right = right;

    return node;
}

// Parse a primary expression (number or expression in parentheses)
struct ExpressionNode *parsePrimary(const char **expr) {
    if (**expr == '(') {
        (*expr)++;
        struct ExpressionNode *result = parseExpression(expr, 0);
        if (**expr == ')') {
            (*expr)++;
        } else {
            fprintf(stderr, "Error: Expected closing parenthesis\n");
            exit(EXIT_FAILURE);
        }
        return result;
    } else if (isalpha(**expr)) {
        if (isalpha(*((*expr) + 1)) || *((*expr) + 1) == '(') {
            return parseFunction(expr);
        } else {
            char variable = parseVariable(expr);
            return createNode(VARIABLE, 0, variable, 0, -1, NULL, NULL);
        }
    } else {
        int operand = parseNumber(expr);
        return createNode(NUMBER, operand, 0, 0, -1, NULL, NULL);
    }
}

// выражения
struct ExpressionNode *parseExpression(const char **expr, int minPrecedence) {
    struct ExpressionNode *leftOperand = parsePrimary(expr);

    while (1) {
        int currentPrecedence = getPrecedence(**expr);

        // Оператор имеет приоритет ниже -
        if (currentPrecedence <= minPrecedence) {
            return leftOperand;
        }

        char op = parseOperator(expr);

        //парсим правый операнд
        struct ExpressionNode *rightOperand = parseExpression(expr, currentPrecedence);

        // новая нода
        leftOperand = createNode(OPERATOR, 0, 0, op, -1, leftOperand, rightOperand);
    }
}

//выводим приорите нод в нотации
void printPrefix(struct ExpressionNode *node) {
    if (node) {
        if (node->type == OPERATOR) {
            printf("%c ", node->op);
        } else if (node->type == NUMBER) {
            printf("%d ", node->operand);
        } else if (node->type == VARIABLE) {
            printf("%c ", node->variable);
        } else if (node->type == FUNCTION) {
            printf("%s ", node->function);
        }
        printPrefix(node->left);
        printPrefix(node->right);
    }
}

static inline char *stringFromEnum(OperationType o)
{
    static const char *strings[] = { "+",
                                     "-",
                                     "*",
                                     "/",
                                     "sin(",
                                     "cos(","tan(","ctan(",
                                     "pow(",
                                     "log(","-("};

    return strings[o];
}

//PLUS,
//MINUS,
//MULTIPLICATION,
//DIVISION,
//SIN,
//COS,
//TAN,
//CTAN,
//POWER,
//LOGARITHM,
//NEGATIVE

void printInfix(struct ExpressionNode *node) {
    if (node) {
        if (node->type == OPERATOR || node->type == FUNCTION) {
            char *operation = stringFromEnum(node->operationType);
            if (operation == "-") {
                printInfix(node->left);
                printf(" - ");
                printInfix(node->right);
            } else
            if (operation == "+") {
                printInfix(node->left);
                printf(" + ");
                printInfix(node->right);
            } else if (operation == "*") {
                printInfix(node->left);
                printf(" * ");
                printInfix(node->right);
            } else if (operation == "/") {
                printInfix(node->left);
                printf(" / ");
                printInfix(node->right);
            } else if (operation == "pow(") {
                printf("%s ", operation);
                printInfix(node->left);
                printf(", ");
                printInfix(node->right);
                printf(")");
            } else {
                printf("%s ", operation);
                printInfix(node->left);
                printf(")");
            }
        }else if (node->type == NUMBER) {
            printf("%.1f", node->operand);
        } else if (node->type == VARIABLE) {
            printf("%c ", node->variable);
        }
    }
}
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