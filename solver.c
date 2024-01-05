#include <stdio.h>
#include "parser.h"
#include "transformer.h"

void solve(char **input){
    Expression *expression = parseInput(input);
    printf("In: ");
    printExpression(expression);
    printf("\n");
    printf("Out: ");
    printExpression(evaluate(expression));
    printf("\n");
    printf("\n");

   // printExpression(evaluateExpression(evaluate(expression)));
   // printf("\n");
}
