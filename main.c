#include <stdio.h>
#include <ctype.h>
#include "tree/parser.h"
#include "algorithm/derivative.h"
#include "algorithm/derivative.c"

int main() {
    const char *input = "sin((pow(x,2)+1))";
    struct ExpressionNode *ast = parseExpression(&input, 0);
    printPrefix(ast);
    struct ExpressionNode * der= derivateExpression(ast);
    printf("Prefix Notation: ");
    printInfix(der);
    printf("\n");


    // освобождаем память для нод
    free(ast);

    return 0;
}
