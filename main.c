#include <stdio.h>
#include "parser.h"
#include "transformer.h"
#include "evaluator.h"

int main() {
    char *input = "set[k[n_],sum[n,1]]";
    char *input2 = "set[f[n_,m_],mul[sum[n,n],m]]";
    char *input3 = "setDelayed[f[p_],sum[p,9]]";
    char *input4 = "k[8]";


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
    addAttrs("k", ALL);
    printContext();

    Expression *d = evaluate(a);
    printTree(evaluateExpression(d));



    return 0;
}
