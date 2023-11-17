#include <stdio.h>
#include <ctype.h>
#include "tree/parser.h"

int main() {
    const char *input = "sin((pow(x,2)+1))";
    struct ExpressionNode *ast = parseExpression(&input, 0);

    printf("Prefix Notation: ");
    printInfix(ast);
    printf("\n");


    // освобождаем память для нод
    free(ast);

    return 0;
}
