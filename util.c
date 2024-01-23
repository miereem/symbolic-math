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
    newNode->hold = 0;
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
    copy->hold = node->hold;

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

void freeExpression(Expression *expr)
 {
     if (expr == NULL)
     {
         return;
     }
     if (expr->symbol != NULL) {
         free(expr->symbol);
     }

     if (expr->children != NULL) {
         for (int i = 0; i < expr->numChildren; ++i) {
             freeExpression(&(expr->children[i]));
         }
         free(expr->children);
     }

     // Free the Expression structure itself
   //  free(expr);
 }

