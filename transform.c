
#include <stdlib.h>
#include <string.h>

#include "transform.h"


static struct Context context = {
        .numNames = 0,

};

void initContext() {
    context.names = malloc(100 * sizeof(char *));
    context.definitions = malloc(100 * sizeof(char *));
}

int isInContext(char *name) {
    for (int i = 0; i < context.numNames; i++) {
        if (strcmp(context.names[i], name)==0) {
            return i;
        }
    }
    return -1;
}
void addDefinition(int index, Expression * expression){
    context.definitions[index] = *expression;
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
    }
    addDefinition(index, node);
    return;
}
