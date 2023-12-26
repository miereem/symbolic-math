#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <printf.h>
#include <stdbool.h>

#include "transformer.h"
#include "evaluator.h"

static struct Context context = {
        .numNames = 0,
};

void initContext() {
    context.names = malloc(sizeof(char *));
    context.definitions = malloc(sizeof(DefinitionArray));
}

int isInContext(char *name) {
    for (int i = 0; i < context.numNames; i++) {
        if (strcmp(context.names[i], name) == 0) {
            return i;
        }
    }
    return -1;
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

void printLocalContext(struct Context context) {
    printf("Context:\n");

    for (size_t i = 0; i < context.numNames; i++) {
        for (size_t j = 0; j < context.definitions[i].size; j++) {
            printf("%s := ", context.names[i]);
            printExpression(&context.definitions[i].definitionArray[j]);
            printf("\n");
        }
        printf("\n");
    }
}

void addDefinition(int index, Expression *expression, bool isNew) {
    if (isNew) {
        context.definitions = realloc(context.definitions, context.numNames * sizeof(DefinitionArray));
        if (context.definitions == NULL) {
            fprintf(stderr, "Memory reallocation error\n");
            return;
        }
        context.definitions[index].size = 0;
        context.definitions[index].definitionArray = malloc(sizeof(Expression));
    }
    context.definitions[index].size++;
    context.definitions[index].definitionArray = realloc(context.definitions[index].definitionArray,
                                                         context.definitions[index].size * sizeof(Expression));
    if (context.definitions[index].definitionArray == NULL) {
        fprintf(stderr, "Memory reallocation error\n");
        return;
    }
    context.definitions[index].definitionArray[context.definitions[index].size - 1] = *expression;
}

int addName(char *symbol) {
    context.numNames++;
    context.names = realloc(context.names, context.numNames * sizeof(char *));
    context.names[context.numNames - 1] = strdup(symbol);
    return context.numNames - 1;
}

void set(struct Expression *node) {
    int index;
    if ((index = isInContext(node->children[0].symbol)) == -1) {
        index = addName(node->children[0].symbol);
        addDefinition(index, node, true);
        return;
    }
    addDefinition(index, node, false);
    return;
}


Expression *findDefinition(DefinitionArray array, Expression *node) {
    // if (node->numChildren > 0 && node->children[0].numChildren > 0) {
    int argNum = node->numChildren;
    for (int i = 0; i < array.size; i++) {
        if (array.definitionArray[i].children[0].numChildren == argNum) {
            return &array.definitionArray[i];
        }
    }
    return &array.definitionArray[0]; //здесь либо хэндл либо return node;
}


Expression *replaceUnknowns(Expression *node) {
    if (strcmp(node->symbol, "set") == 0) {
        set(node);
        return node;
    }
    for (size_t i = 0; i < context.numNames; i++) {
        if (strcmp(node->symbol, context.names[i]) == 0) {
            Expression *setTree = findDefinition(context.definitions[i], node);
            //check if the returned node != sent node
            return compareAndAddToContext(node, setTree);
        }
    }
    for (int i = 0; i < node->numChildren; i++) {
        node->children[i] = *replaceUnknowns(&node->children[i]);
    }
    return node;

}


Expression *replacePatterns(Expression *node, struct Context *localContext) {
    Expression *definedExpression = copyNode(node);
    for (size_t i = 0; i < localContext->numNames; i++) {
        if (strcmp(definedExpression->symbol, localContext->names[i]) == 0) {
            return &localContext->definitions[i].definitionArray[0];
        }
    }

    for (int i = 0; i < node->numChildren; i++) {
        definedExpression->children[i] = *replacePatterns(&node->children[i], localContext);
    }

    return definedExpression;
}

Expression *replaceRightChild(Expression *node, struct Context *localContext) {
    Expression *definedExpression = copyNode(node);
    if (node->numChildren > 1) {
        definedExpression = replacePatterns(definedExpression, localContext);
    }
    return definedExpression;
}


Expression *compareAndAddToContext(Expression *inputTree, Expression *setTree) {
    struct Context localContext;
    localContext.numNames = 0;
    localContext.names = NULL;
    localContext.definitions = NULL;
    Expression *rightNode = &setTree->children[1];
    Expression *leftNode = &setTree->children[0];

    for (int i = 0; i < inputTree->numChildren; i++) {
        if (strcmp(leftNode->children[i].symbol, "Pattern") == 0) {
            char *patternName = strdup(leftNode->children[i].children[0].symbol);

            localContext.numNames++;
            localContext.names = (char **) realloc(localContext.names, localContext.numNames * sizeof(char *));
            localContext.names[localContext.numNames - 1] = strdup(patternName);

            localContext.definitions = (DefinitionArray *) realloc(
                    localContext.definitions, localContext.numNames * sizeof(DefinitionArray));

            localContext.definitions[localContext.numNames - 1].size = 1;
            localContext.definitions[localContext.numNames - 1].definitionArray =
                    (Expression *) malloc(sizeof(Expression));
            *localContext.definitions[localContext.numNames - 1].definitionArray = inputTree->children[i];
        }
    }

    return replaceRightChild(rightNode, &localContext);


}


int expressionsEqual(Expression *expr1, Expression *expr2) {
    if (strcmp(expr1->symbol, expr2->symbol) != 0 || expr1->numChildren != expr2->numChildren) {
        return 0;
    }

    for (int i = 0; i < expr1->numChildren; i++) {
        if (!expressionsEqual(&expr1->children[i], &expr2->children[i])) {
            return 0;
        }
    }

    return 1;
}


Expression *evaluate(Expression *expression) {
    // Expression *result = expression;
    Expression *prevResult = NULL;

    while (prevResult == NULL || strcmp(expression->symbol, prevResult->symbol) != 0) {
        if (prevResult != NULL) {
            free(prevResult->children);
            free(prevResult);
        }


        prevResult = (Expression *) malloc(sizeof(Expression));
        *prevResult = *expression;

        expression = replaceUnknowns(expression);
        printExpression(expression);
        printf("\n");
    }
    return expression;
}

int isOperator(char *symbol) {
    return strcmp(symbol, "sum") == 0 || strcmp(symbol, "mul") == 0;
}

Expression *evaluateExpression(Expression *node) {
    if (node == NULL) {
        return NULL;
    }

    if (node->numChildren == 0) {
        return createNode(node->symbol);
    }

    for (int i = 0; i < node->numChildren; i++) {
        node->children[i] = *evaluateExpression(&node->children[i]);
    }

    if (isOperator(node->symbol)) {
        int allChildrenEvaluated = 1;
        for (int i = 0; i < node->numChildren; i++) {
            if (isOperator(node->children[i].symbol)) {
                allChildrenEvaluated = 0;
                break;
            }
        }

        if (allChildrenEvaluated) {
            if (strcmp(node->symbol, "sum") == 0) {
                Expression *res = sum(node);
                free(node->children);
                node->children = NULL;
                node->numChildren = 0;
                node = res;

            } else if (strcmp(node->symbol, "mul") == 0) {
                Expression *res = mul(node);
                free(node->children);
                node->children = NULL;
                node->numChildren = 0;
                node = res;
            }
        }
    }

    return node;
}

void printContext() {
    printf("Context:\n");

    for (size_t i = 0; i < context.numNames; i++) {
        for (size_t j = 0; j < context.definitions[i].size; j++) {
            printf("%s := ", context.names[i]);
            printExpression(&context.definitions[i].definitionArray[j]);
            printf("\n");
        }
        printf("\n");
    }
}

