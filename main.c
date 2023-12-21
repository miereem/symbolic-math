#include <stdio.h>
#include "parser.c"

int main() {
    char *input = "set[sum[2,3],5];";
    // solve(&input);

    struct Expression* root = parseExpression(&input);


    printf("Tree: ");
    printTree(root);
    printf("\n");



    return 0;
}
