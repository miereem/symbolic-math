//
// Created by Home on 22.12.2023.
//

#ifndef SYMBOLIC_STRUCTURES_H
#define SYMBOLIC_STRUCTURES_H
typedef struct Expression {
    char *symbol;
    struct Expression *children;
    int numChildren;
} Expression;

void printTree(Expression *root);

void addChild(Expression *parent, Expression *child);

Expression *createNode(char *symbol);

Expression *copyNode(Expression *node);

#endif //SYMBOLIC_STRUCTURES_H
