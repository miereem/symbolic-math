//
// Created by yfcni on 12/21/2023.
//

#ifndef SYMBOLIC_STRUCTURES_H
#define SYMBOLIC_STRUCTURES_H
typedef struct Expression
{
    char *symbol;
    struct Expression *children;
    int numChildren;
} Expression;
void printTree(Expression *root);
void addChild(Expression *parent, Expression *child);
Expression *createNode(char *symbol);
#endif //SYMBOLIC_STRUCTURES_H
