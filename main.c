#include <stdio.h>
#include "parser.c"

int main() {
    char *input = "set[2,5]";
    // solve(&input);

    struct Expression* root = parseExpression(&input);

//    printf(&(root->children->symbol));
//    printf(((Expression*)(root->children+sizeof(Expression))->symbol));
//    printf("Tree: ");
//    printf("\n");
    printTree(root);
    printf("\n");



    return 0;
}
