#include <stdio.h>
#include <stdlib.h>

// typedef enum type
// {
//     CONSTANT,
//     SYMBOL,
//     FUNCTION
// } TokenType;

typedef struct Expression
{
    char *symbol;
    struct Expression *children;
    int numChildren;
} Expression;

Expression *createNode(char *symbol)
{
    Expression *newNode = (Expression *)malloc(sizeof(Expression));
    newNode->symbol = symbol;
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

void printTree(Expression *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%s ", root->symbol);

    for (int i = 0; i < root->numChildren; i++)
    {
        printTree(&(root->children[i]));
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

// symbol and object

// List, Pattern, Set, SetDelayed,