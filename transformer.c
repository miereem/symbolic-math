#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdbool.h>
#include <stdio.h>

#include "transformer.h"
#include "evaluator.h"
#include "util.h"
#include "parser.h"
#include "graph.h"


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

    for (int i = 0; i < context.definitions[index].size; i++) {
        if (expressionsEqual(&expression->children[0],&context.definitions[index].definitionArray[i].children[0])) {
            context.definitions[index].definitionArray[i] = *expression;
            return;
        }
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

void addAttrs(char *name, enum Hold attr) {
    int index;
    if ((index = isInContext(name)) != -1) {
        for (int i = 0; i < context.definitions[index].size; i++) {
            context.definitions[index].definitionArray[i].children[1].hold = attr;
        }
    }
}

int
argumentsMatch(Expression *definition, Expression *node) { //0 - arguments match ,  1 - default, 2 - has no definition
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
    int argNum = node->numChildren;
    Expression *defaultDefinition = NULL;
    for (int i = 0; i < array.size; i++) {
        if (array.definitionArray[i].numChildren > 0) {
            if (array.definitionArray[i].children[0].numChildren == argNum) {
//                printf("\n");
//                printExpression(node);
//                printf(" --- ");
//                printExpression(&array.definitionArray[i].children[0]);
//                printf("  ---  ");
//                printf("%d",(argumentsMatch(&array.definitionArray[i].children[0], node)));
//                printf("\n");
                if (argumentsMatch(&array.definitionArray[i].children[0], node) == 0) {
                    return &array.definitionArray[i];
                }
                if (argumentsMatch(&array.definitionArray[i].children[0], node) == 1) {
                    defaultDefinition = &array.definitionArray[i];
                }
            }
        }
    }
    if (defaultDefinition != NULL) {
        return defaultDefinition;
    }
    return node;
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

Expression *append(struct Expression *node) {
    if (node->numChildren == 0) {
        return node;
    }
    Expression *setTree = NULL;
    for (size_t i = 0; i < context.numNames; i++) {
        if (strcmp(node->children[0].symbol, context.names[i]) == 0) {
            setTree = findDefinition(context.definitions[i], &node->children[0]);
        }
    }
    if (setTree != NULL) {
        if (strcmp(setTree->children[1].children[0].symbol, "") == 0) {
            setTree->children[1].children[0] = node->children[1];
        } else {
            addChild(&setTree->children[1], &node->children[1]);
        }
    }
    return node;
}


Expression *len(struct Expression *node) {
    if (node->numChildren == 0) {
        return node;
    }
    Expression *setTree = NULL;
    for (size_t i = 0; i < context.numNames; i++) {
        if (strcmp(node->children[0].symbol, context.names[i]) == 0) {
            setTree = findDefinition(context.definitions[i], &node->children[0]);
        }
    }
    if (setTree != NULL) {
        if (strcmp(setTree->children[1].children[0].symbol,"") == 0) {
            return createNode("0");
        } else {
            char symbol[100];
            sprintf(symbol, "%d", setTree->children[1].numChildren);
            return createNode(symbol);
        }
    }
    return node;
}


Expression *first(struct Expression *node) {
    if (node->numChildren == 0) {
        return node;
    }
    Expression *setTree = NULL;
    for (size_t i = 0; i < context.numNames; i++) {
        if (strcmp(node->children[0].symbol, context.names[i]) == 0) {
            setTree = findDefinition(context.definitions[i], &node->children[0]);
        }
    }
    if (setTree != NULL) {
        if (strcmp(setTree->children[1].children[0].symbol,"") == 0) {
            return createNode("Null");
        } else {
            return createNode(setTree->children[1].children[0].symbol);
        }
    }
    return node;
}

//Append(list, item)
//Prepend(list, item)
//Rest(list)
//Last(list)
//First(list)
//Head(list)
//Length(list)


int isOperator(char *symbol) {
    return strcmp(symbol, "sum") == 0 || strcmp(symbol, "mul") == 0 || strcmp(symbol, "div") == 0 ||
           strcmp(symbol, "less") == 0 || strcmp(symbol, "more") == 0 || strcmp(symbol, "plot") == 0 ||
           strcmp(symbol, "numberQ") == 0 || strcmp(symbol, "append") == 0 || strcmp(symbol, "len") == 0;
}

Expression *replaceUnknowns(Expression *node) {
//    printf("replace \n");
//    printExpression(node);
//    printf("\n");
//    printContext();
    if (node == NULL) {
        return NULL;
    }
    if (strcmp(node->symbol, "append") == 0) {
        node->hold = FIRST;
    }

    if (strcmp(node->symbol, "len") == 0) {
        return len(node);
    }
    if (strcmp(node->symbol, "first") == 0) {
        return first(node);
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
            hold = ALL;
        }
        if (strcmp(node->children[1].symbol, "holdFirst") == 0) {
            hold = FIRST;
        }
        if (strcmp(node->children[1].symbol, "holdRest") == 0) {
            hold = REST;
        }
        addAttrs(node->children[0].symbol, hold);
        return node;
    }

    if (node->hold == 0) {
        for (int i = 0; i < node->numChildren; i++) {
            node->children[i] = *replaceUnknowns(&node->children[i]);
        }
    }


    if (node->hold == 1) {
        return node;
    }

    if (node->hold == 2) {
        for (int i = 1; i < node->numChildren; i++) {
            node->children[i] = *replaceUnknowns(&node->children[i]);
        }
    }
    if (node->hold == 3) {
        for (int i = 0; i < 2; i++) {
            node->children[i] = *replaceUnknowns(&node->children[i]);
        }
    }


    if (isOperator(node->symbol)) {
        int allChildrenEvaluated = 1;
//        for (int i = 0; i < node->numChildren; i++) {
//            if (isOperator(node->children[i].symbol)) {
//                allChildrenEvaluated = 0;
//                break;
//            }
//        }
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

            } else if (strcmp(node->symbol, "div") == 0) {
                Expression *res = divide(node);
                free(node->children);
                node->children = NULL;
                node->numChildren = 0;
                node = res;
            } else if (strcmp(node->symbol, "less") == 0) {
                Expression *res = less(node);
                free(node->children);
                node->children = NULL;
                node->numChildren = 0;
                node = res;
            } else if (strcmp(node->symbol, "more") == 0) {
                Expression *res = more(node);
                free(node->children);
                node->children = NULL;
                node->numChildren = 0;
                node = res;
            } else if (strcmp(node->symbol, "plot") == 0) {
//                node->children = evaluate(node->children);
//                struct PlotDTO *plotDto = parsePLot(node);
//                plot(plotDto->plots, plotDto->width, plotDto->height);
                return node;
            } else if (strcmp(node->symbol, "numberQ") == 0) {
                Expression *res = numberQ(node);
                free(node->children);
                node->children = NULL;
                node->numChildren = 0;
                node = res;
            } else if (strcmp(node->symbol, "append") == 0) {
                Expression *res = append(node);
                free(node->children);
                node->children = NULL;
                node->numChildren = 0;
                node = res;
            }
        }
    }


    for (size_t i = 0; i < context.numNames; i++) {
        if (strcmp(node->symbol, context.names[i]) == 0) {
            Expression *setTree = findDefinition(context.definitions[i], node);

            if (expressionsEqual(setTree, node)) {
                return node;
            }
            return compareAndAddToContext(node, setTree);
        }
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
    if (node->numChildren >= 0) {
        definedExpression = replacePatterns(definedExpression, localContext);
    }
    return definedExpression;
}

void cacheExpression(Expression node, Expression *setTree) {
    Expression definition = *copyNode(evaluate(setTree));
    Expression *expr = createNode("set");
    addChild(expr, &node);
    addChild(expr, &definition);
    set(expr, false);
}


void patternMatch(Expression *inputTree, Expression *leftNode, struct Context *localContext) {
    if (leftNode == NULL) {
        return;
    }

    for (int i = 0; i < inputTree->numChildren; i++) {
//            printf("\n");
//            printExpression(inputTree);
//            printf("  ---  ");
//            printExpression(leftNode);
//            printf("\n");

        if (inputTree->children[i].numChildren > 0 && leftNode->children[i].numChildren > 0 &&
            strcmp(leftNode->children[i].symbol, "Pattern") != 0) {
            patternMatch(&inputTree->children[i], &leftNode->children[i], localContext);
        } else {
            if (strcmp(leftNode->children[i].symbol, "Pattern") == 0) {
                char *patternName = strdup(leftNode->children[i].children[0].symbol);

                localContext->numNames++;
                localContext->names = (char **) realloc(localContext->names, localContext->numNames * sizeof(char *));
                localContext->names[localContext->numNames - 1] = strdup(patternName);

                localContext->definitions = (DefinitionArray *) realloc(
                        localContext->definitions, localContext->numNames * sizeof(DefinitionArray));

                localContext->definitions[localContext->numNames - 1].size = 1;
                localContext->definitions[localContext->numNames - 1].definitionArray =
                        (Expression *) malloc(sizeof(Expression));
                *localContext->definitions[localContext->numNames - 1].definitionArray = inputTree->children[i];
            }
        }
    }
//    printLocalContext(*localContext);
//        printf("\n");

}

Expression *compareAndAddToContext(Expression *inputTree, Expression *setTree) {
    struct Context localContext;
    localContext.numNames = 0;
    localContext.names = NULL;
    localContext.definitions = NULL;
    Expression *rightNode = &setTree->children[1];
    Expression *leftNode = &setTree->children[0];

    patternMatch(inputTree, leftNode, &localContext);


    // cacheExpression(*inputTree, replaceUnknowns(replaceRightChild(rightNode, &localContext)));
    return replaceRightChild(rightNode, &localContext);
}

Expression *evaluate(
        Expression *expression) {
    Expression *prevResult = NULL;
    while (prevResult == NULL || expressionsEqual(expression, prevResult) == 0) {
        if (prevResult != NULL) {
            free(prevResult->children);
            free(prevResult);
        }


        prevResult = (Expression *) malloc(sizeof(Expression));
        *prevResult = *copyNode(expression);

        expression = replaceUnknowns(expression);
    }
    // expression = replaceUnknowns(expression);

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

