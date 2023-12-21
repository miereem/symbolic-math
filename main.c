#include <stdio.h>
#include "parser.h"
#include "transform.h"
#include "evaluate.h"

int main() {
    char *input = "set[k[pattern[n],sum[n,1]]";
//    char *input1 = "set[]";
    char *input2 = "set[k,7]";
    // solve(&input);

    initContext();
    printTree(sum( parseExpression(&input)));
    set( parseExpression(&input2));

//    printf(&(root->children->symbol));
//    printf(((Expression*)(root->children+sizeof(Expression))->symbol));
    printf("Tree: ");
//    printf("\n");
//    printTree(root);
    printf("\n");



    return 0;
}
