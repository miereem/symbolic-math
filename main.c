#include <stdio.h>
#include <ctype.h>
#include "tree/parser.h"

int main() {
    const char *input = "f(x)";
    struct ExpressionNode *ast = parseExpression(&input, 0);

    printf("Prefix Notation: ");
    printPrefix(ast);
    printf("\n");


    // освобождаем память для нод
    free(ast);

    return 0;
}
