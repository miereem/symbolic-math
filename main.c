#include <stdio.h>
#include "parser.h"
#include "transformer.h"
#include "evaluator.h"

int main() {
    char *input = "set[k,1]";
    char *input2 = "set[f[n_,m_],mul[sum[n,n],m]]";
    char *input3 = "set[f[p_],sum[p,9]]";
    char *input4 = "f[5,1,7]";


    initContext();

    Expression *e = parseInput(&input);
    Expression *a = parseInput(&input4);
    Expression *b = parseInput(&input3);
    Expression *c = parseInput(&input2);


    printTree(evaluate(b));
    printTree(evaluate(e));

    printf("\n");
    printTree(evaluate(c));

    printf("\n");
    printContext();

    Expression *d = evaluate(a);
    printTree(evaluateExpression(d));



    return 0;
}
