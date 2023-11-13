#include <stdio.h>
#include <stdlib.h>

enum TokenType {
    NUMBER,
    OPERATOR,
    VARIABLE
};


struct ExpressionNode {
    enum TokenType type;
    // можно будет если нужно добавить тип опеарации пока хз зач
    union {
        int operand;        //  NUMBER nodes
        char variable; // VARIABLE
        char op;            //  OPERATOR nodes
    };
    struct ExpressionNode *left;
    struct ExpressionNode *right;
};

int parseNumber(const char **expr);
char parseOperator(const char **expr);
struct ExpressionNode* parseExpression(const char **expr, int minPrecedence);
struct ExpressionNode* parsePrimary(const char **expr);

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
struct ExpressionNode* createNode(enum TokenType type, int operand, char variable, char op, struct ExpressionNode *left, struct ExpressionNode *right) {
    struct ExpressionNode *node = (struct ExpressionNode *)malloc(sizeof(struct ExpressionNode));
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
    }
    node->left = left;
    node->right = right;

    return node;
}

// Parse a primary expression (number or expression in parentheses)
struct ExpressionNode* parsePrimary(const char **expr) {
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
    } else if (**expr >= 'a' && **expr <= 'z') {
        char variable = parseVariable(expr);
        return createNode(VARIABLE, 0, variable, 0, NULL, NULL);
    } else {
        int operand = parseNumber(expr);
        return createNode(NUMBER, operand, 0,0, NULL, NULL);
    }
}

// выражения
struct ExpressionNode* parseExpression(const char **expr, int minPrecedence) {
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
        leftOperand = createNode(OPERATOR, 0, 0, op, leftOperand, rightOperand);
    }
}

//выводим приорите нод в нотации 
void printPostfix(struct ExpressionNode *node) {
    if (node) {
        printPostfix(node->left);
        printPostfix(node->right);
        if (node->type == NUMBER) {
            printf("%d ", node->operand);
        } else if (node->type == VARIABLE) {
            printf("%c ", node->variable);
        } else if (node->type == OPERATOR) {
            printf("%c ", node->op);
        }
    }
}

int main() {
    const char *input = "((3+c)*a)-7";
    struct ExpressionNode *ast = parseExpression(&input, 0);

    printf("Postfix Notation: ");
    printPostfix(ast);
    printf("\n");


    // освобождаем память для нод
    free(ast);

    return 0;
}
