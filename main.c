#include <stdio.h>
#include <ctype.h>
#include "tree/parser.h"
#include "algorithm/derivative.h"
#include "algorithm/derivative.c"

int main() {
    const char *input = "cos((pow(x,2)+1))";
    struct ExpressionNode *ast = parseExpression(&input, 0);
    struct ExpressionNode * der= derivateExpression(ast);
    printInfix(der);
    printf("\n");

    free(ast);

    return 0;
}
