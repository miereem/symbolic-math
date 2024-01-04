#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

Expression *createNode(char *symbol)
{
    Expression *newNode = (Expression *)malloc(sizeof(Expression));
    newNode->symbol = strdup(symbol);
    newNode->children = NULL;
    newNode->numChildren = 0;
    return newNode;
}



void addChild(Expression *parent, Expression *child)
{
    parent->numChildren++;
    parent->children = (Expression *)realloc(parent->children, parent->numChildren * sizeof(Expression));
    parent->children[parent->numChildren - 1] = *child;
}

Expression *copyNode(Expression *node) {
    if (node == NULL) {
        return NULL;
    }

    Expression *copy = createNode(node->symbol);

    for (int i = 0; i < node->numChildren; i++) {
        Expression *childCopy = copyNode(&node->children[i]);
        addChild(copy, childCopy);
    }

    return copy;
}

void printExpression(Expression *node) {
    printf("%s", node->symbol);
    if (node->numChildren > 0) {
        printf("[");
        for (int i = 0; i < node->numChildren; i++) {
            printExpression(&node->children[i]);
            if (i < node->numChildren - 1) {
                printf(", ");
            }
        }
        printf("]");
    }
}
// void freeTree(Expression *root)
// {
//     if (root == NULL)
//     {
//         return;
//     }

//     for (int i = 0; i < root->numChildren; i++)
//     {
//         freeTree(&(root->children[i]));
//     }

//     free(root->children); // Free the array of child nodes
//     free(root);
// }

