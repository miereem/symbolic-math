
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "transform.h"


static struct Context context = {
        .numNames = 0,

};

void initContext() {
    context.names = malloc(sizeof(char *));
    context.definitions = malloc( sizeof(DefinitionArray));
}

int isInContext(char *name) {
    for (int i = 0; i < context.numNames; i++) {
        if (strcmp(context.names[i], name)==0) {
            return i;
        }
    }
    return -1;
}
void addDefinition(int index, Expression * expression, bool isNew){
    if(isNew){
        context.definitions = realloc(context.definitions, context.numNames * sizeof(DefinitionArray));
        if (context.definitions == NULL) {
            fprintf(stderr, "Memory reallocation error\n");
            return;  // Exit with an error code
        }
        context.definitions[index].size=0;
        context.definitions[index].definitionArray=malloc( sizeof(Expression));
    }
    context.definitions[index].size++;
    context.definitions[index].definitionArray = realloc(context.definitions[index].definitionArray, context.definitions[index].size * sizeof(Expression));
    if (context.definitions[index].definitionArray == NULL) {
        fprintf(stderr, "Memory reallocation error\n");
        return;  // Exit with an error code
    }
    context.definitions[index].definitionArray[context.definitions[index].size - 1]=*expression;
}
int addName(char * symbol){
    context.numNames++;
    context.names = realloc(context.names, context.numNames * sizeof(char *));
    context.names[context.numNames - 1] = strdup(symbol);
    return context.numNames - 1;
}

void set(struct Expression* node) {
    int index;
    if ((index=isInContext(node->children[0].symbol))==-1) {
        index = addName(node->children[0].symbol);
        addDefinition(index, node, true);
        return;
    }
    addDefinition(index, node, false);
    return;
}
