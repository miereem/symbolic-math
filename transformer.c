#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdbool.h>
#include <stdio.h>

#include "transformer.h"
#include "evaluator.h"
#include "util.h"


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

int isDefaultDefinition(Expression *expression) {
    int cnt = 0;
    for (size_t i = 0; i < expression->numChildren; i++) {
        if (strcmp(expression->children[i].symbol, "Pattern") == 0) {
            cnt++;
        }
    }
    if (cnt == expression->numChildren) {
        return 1;
    }
    return 0;
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
void addAttrs(char* name, enum Hold attr){
    int index;
    if((index = isInContext(name))!=-1){
        for (int i = 0; i < context.definitions[index].size; i++) {
            context.definitions[index].definitionArray[i].children[1].hold = attr;
           // printf("mn %d ", context.definitions[index].definitionArray[i].hold);

        }
    }
}

int argumentsMatch(Expression *definition, Expression *node) { //0 - arguments match ,  1 - default, 2 - has no definition
    int cnt = 0;
    for (size_t i = 0; i < definition->numChildren; i++) {
        if (strcmp(node->children[i].symbol, definition->children[i].symbol) != 0 &&
            strcmp(definition->children[i].symbol, "Pattern") != 0) {
            return 2;
        }
        if (strcmp(definition->children[i].symbol, "Pattern") == 0) {
            cnt++;
        }
    }
    if (cnt == definition->numChildren) {
        return 1;
    }
    return 0;
}

Expression *findDefinition(DefinitionArray array, Expression *node) {
//    printExpression(node);
    int argNum = node->numChildren;
    Expression *defaultDefinition = NULL;
    for (int i = 0; i < array.size; i++) {
        if (array.definitionArray[i].numChildren > 0) {
            if (array.definitionArray[i].children[0].numChildren == argNum) {
                if (argumentsMatch(&array.definitionArray[i].children[0], node) == 0 ) {
                    return &array.definitionArray[i];
                }
                if (argumentsMatch(&array.definitionArray[i].children[0], node) == 1) {
                    defaultDefinition = &array.definitionArray[i];
                }
            }
        }
    }
    if (defaultDefinition != NULL ) {
        return defaultDefinition;
    }
    return node;
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

void set(struct Expression *node, bool isDelayed) {

    int index;
    if (isDelayed == false) {
        node->children[1] = *copyNode(evaluate(&node->children[1]));
    }
    if ((index = isInContext(node->children[0].symbol)) == -1) {
        index = addName(node->children[0].symbol);
        addDefinition(index, node, true);
    } else {
        if (!expressionsEqual(findDefinition(context.definitions[index], &node->children[0]), node)) {
            addDefinition(index, node, false);
        }
    }
    return;
}

int isOperator(char *symbol) {
    return strcmp(symbol, "sum") == 0 || strcmp(symbol, "mul") == 0;
}

Expression *replaceUnknowns(Expression *node) {
//    printf("\nnode\n");
//    printExpression(node);
//    printf("\nnode\n");


    if (node == NULL) {
        return NULL;
    }
    if (node->numChildren == 0) {
        return node;
    }

    if (strcmp(node->symbol, "set") == 0) {
        set(node, false);
        return node;
    }
    if (strcmp(node->symbol, "setDelayed") == 0) {
        set(node, true);
        return node;
    }
    if (strcmp(node->symbol, "hold") == 0) {
        return node;
    }
    if (strcmp(node->symbol, "addAttrs") == 0) {
        enum Hold hold = 0;
        if (strcmp(node->children[1].symbol, "holdAll") == 0) {
            hold = 1;
        }
        if (strcmp(node->children[1].symbol, "holdFirst") == 0) {
            printf("holdf ");
            hold = 2;
        }
        if (strcmp(node->children[1].symbol, "holdRest") == 0) {
            hold = 3;
        }
        addAttrs(node->children[0].symbol, hold);
        return node;
    }
    if(node->hold == 0) {
        for (int i = 0; i < node->numChildren; i++) {
            node->children[i] = *replaceUnknowns(&node->children[i]);
        }
    }
    if(node->hold == 1) {
        return node;
    }
    if(node->hold == 2) {
        for (int i = 1; i < node->numChildren; i++) {
            node->children[i] = *replaceUnknowns(&node->children[i]);
        }
    }
    if(node->hold == 3) {
        for (int i = 0; i < 2; i++) {
            node->children[i] = *replaceUnknowns(&node->children[i]);
        }
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

    for (size_t i = 0; i < context.numNames; i++) {
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


        if (strcmp(node->symbol, context.names[i]) == 0) {
            Expression *setTree = findDefinition(context.definitions[i], node);

            if (expressionsEqual(setTree, node)) {
                return node;
            }
            return compareAndAddToContext(node, setTree);
        }
    }





    printExpression(node);
    printf("\n");
    printf("\n");

    return node;

}


Expression *replacePatterns(Expression *node, struct Context *localContext) {
    printf("\n");
    printExpression(node);
    printf("\n");
    Expression *definedExpression = copyNode(node);
    for (size_t i = 0; i < localContext->numNames; i++) {
        if (strcmp(definedExpression->symbol, localContext->names[i]) == 0) {
            return &localContext->definitions[i].definitionArray[0];
        }
    }
    for (int i = 0; i < node->numChildren; i++) {
        definedExpression->children[i] = *replacePatterns(&node->children[i], localContext);
    }
    printExpression(definedExpression);
    printf("\n");
    return definedExpression;
}

Expression *replaceRightChild(Expression *node, struct Context *localContext) {
    printf("mm \n");
    printLocalContext(*localContext);
    printExpression(node);
    printf(" %d \n", node->numChildren );
    Expression *definedExpression = copyNode(node);
    if (node->numChildren > 0) {
        definedExpression = replacePatterns(definedExpression, localContext);
    }
    printf("def ");
    printExpression(definedExpression);
    printf("\n");
    //printf("%d ", definedExpression->hold);
    return definedExpression;

}

void cacheExpression(Expression node, Expression *setTree) {
    Expression definition = *copyNode(evaluate(setTree));
    Expression *expr = createNode("set");
    addChild(expr,&node);
    addChild(expr,&definition);
    set(expr,false);
}

Expression *compareAndAddToContext(Expression *inputTree, Expression *setTree) {
    struct Context localContext;
    localContext.numNames = 0;
    localContext.names = NULL;
    localContext.definitions = NULL;
    Expression *rightNode = &setTree->children[1];
    Expression *leftNode = &setTree->children[0];
    printExpression(leftNode);
    printf("   ");
    printExpression(rightNode);
    printf("\n");
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



    printExpression(rightNode);
    printf("   ");
    printExpression(leftNode);
    printf("\n");

   // cacheExpression(*inputTree, replaceUnknowns(replaceRightChild(rightNode, &localContext)));

    return replaceRightChild(rightNode, &localContext);



}


Expression *evaluate(
        Expression *expression) {
    Expression *prevResult = NULL;
    while (prevResult == NULL || expressionsEqual(expression, prevResult)  == 0) {
        if (prevResult != NULL) {
            free(prevResult->children);
            free(prevResult);
        }


        prevResult = (Expression *) malloc(sizeof(Expression));
        *prevResult = *copyNode(expression);

        expression = replaceUnknowns(expression);
//        printExpression(prevResult);
//        printf("  ");
//        printExpression(expression);
//        printf("\n");

    }
    return expression;
}




void printContext() {
    printf("\nContext:\n");

    for (size_t i = 0; i < context.numNames; i++) {
        for (size_t j = 0; j < context.definitions[i].size; j++) {
            printf("%s := ", context.names[i]);
            printExpression(&context.definitions[i].definitionArray[j]);
            printf("\n");
        }

        printf("\n");
    }
}

