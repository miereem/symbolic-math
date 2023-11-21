#include <stdio.h>
#include <ctype.h>
#include "tree/parser.h"
#include "algorithm/derivative/derivative.h"
#include "algorithm/integral/integral.h"

int main() {
    const char *input = "1/(pow(x,2)+pow(a,2))";
    struct ExpressionNode *ast = parseExpression(&input, 0);
//    struct ExpressionNode * der= derivateExpression(ast);
    struct ExpressionNode * integral= make_integral(ast);
//    printInfix(der);
    printInfix(integral);
    printf("\n");

    free(ast);

    return 0;
}
