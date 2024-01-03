#include <stdio.h>
#include "parser.h"
#include "transformer.h"
#include "evaluator.h"
void solve(char **input){
    Expression *expression = parseInput(input);
    printExpression(evaluateExpression(evaluate(expression)));
    printf("\n");
}
