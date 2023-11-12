#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Типы токенов
typedef enum {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END
} TokenType;

// Структура токена
typedef struct {
    TokenType type;
    int value;  // Для NUMBER
} Token;

// Глобальная переменная для хранения текущего токена
Token currentToken;

// Прототипы функций
void getNextToken();
int parseExpression();
int parsePrimary();
int parseUnary();
int parseNumber();

// Функция для вывода сообщения об ошибке
void error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// Функция для получения следующего токена из входной строки
void getNextToken() {
    char c = getchar();

    while (isspace(c)) {
        c = getchar();
    }

    if (isdigit(c)) {
        ungetc(c, stdin);
        scanf("%d", &currentToken.value);
        currentToken.type = NUMBER;
    } else {
        switch (c) {
            case '+':
                currentToken.type = ADD;
                break;
            case '-':
                currentToken.type = SUBTRACT;
                break;
            case '*':
                currentToken.type = MULTIPLY;
                break;
            case '/':
                currentToken.type = DIVIDE;
                break;
            case '(':
                currentToken.type = LPAREN;
                break;
            case ')':
                currentToken.type = RPAREN;
                break;
            case '\n':
            case EOF:
                currentToken.type = END;
                break;
            default:
                error("Invalid character in input");
        }
    }
    // printf("%d",(currentToken.value));
    // printf("lala");
    // printf("%c",(char) currentToken.type);
}

// Функция для парсинга выражения
int parseExpression() {
    int left = parseUnary();

    while (currentToken.type == ADD || currentToken.type == SUBTRACT) {
        Token op = currentToken;
        getNextToken();
        int right = parseUnary();
        if (op.type == ADD) {
            left += right;
        } else {
            left -= right;
        }
    }

    return left;
}

// Функция для парсинга первичных выражений
int parsePrimary() {
    int result;

    switch (currentToken.type) {
        case NUMBER:
            result = currentToken.value;
            getNextToken();
            break;
        case LPAREN:
            getNextToken();
            result = parseExpression();
            if (currentToken.type != RPAREN) {
                error("Expected closing parenthesis");
            }
            getNextToken();
            break;
        default:
            error("Unexpected token in primary expression");
    }

    return result;
}

// Функция для парсинга унарных выражений
int parseUnary() {
    if (currentToken.type == ADD || currentToken.type == SUBTRACT) {
        Token op = currentToken;
        getNextToken();
        int operand = parseUnary();
        if (op.type == SUBTRACT) {
            return -operand;
        }
        return operand;
    } else {
        return parsePrimary();
    }
}

int main() {
    while (1) {
        printf("Enter an expression: ");
        getNextToken();

        if (currentToken.type == END) {
            break;
        }

        int result = parseExpression();

        printf("Result: %d\n", result);
    }

    return 0;
}
