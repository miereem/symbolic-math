#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

struct PlotDTO * parsePLot(Expression *expression) {
    printExpression(expression);
    struct PlotDTO* plotDto = malloc(sizeof (struct PlotDTO));
    if (expression->numChildren != 3) {
        fprintf(stderr, "plot must have 3 parameters\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(expression->children[0].symbol, "s") != 0) {
        fprintf(stderr, "head must be s\n");
        exit(EXIT_FAILURE);
    }
    struct Plots *plots = malloc(sizeof(struct Plots));
    plots->count = expression->children[0].numChildren;
    plots->plots = malloc(sizeof(PointArray) * plots->count);
    for (int i = 0; i < expression->children[0].numChildren; i++) {
        if (strcmp(expression->children[0].children[i].symbol, "l") != 0) {
            fprintf(stderr, "head must be l\n");
            exit(EXIT_FAILURE);
        }
        plots->plots[i].count = expression->children[0].children[i].numChildren;
        plots->plots[i].points = malloc(sizeof(struct Point) * plots->plots[i].count);
        for (int pointN = 0; pointN < expression->children[0].children[i].numChildren; pointN++) {
            if (strcmp(expression->children[0].children[i].children[pointN].symbol, "p") != 0
                ||
                expression->children[0].children[i].children[pointN].numChildren != 2) {
                fprintf(stderr, "head must be p\n");
                exit(EXIT_FAILURE);
            }
            plots->plots[i].points[pointN].x = atof(expression->children[0].children[i].children[pointN].children[0].symbol);
            plots->plots[i].points[pointN].y = atof(expression->children[0].children[i].children[pointN].children[1].symbol);

        }
    }
    plotDto->width = atoi(expression->children[1].symbol);
    plotDto->height = atoi(expression->children[2].symbol);
    plotDto->plots = *plots;
    return plotDto;
}

void substring(char *s, char *sub, int p, int l) {
    int c = 0;

    while (c < l) {
        *(sub + c) = *(s + (p + c));
        c++;
    }
    sub[c] = '\0';
}

bool isChild(char s, int d) {
    if (s == ',' && d == 0 || s == '\0') { //why?
        return false;
    }
    return true;
}

void separateString(const char *input, char **beforeUnderscore, char **afterUnderscore) {
    const char *underscorePos = strchr(input, '_');

    if (underscorePos != NULL) {
        size_t beforeLength = underscorePos - input;

        *beforeUnderscore = malloc(beforeLength + 1);
        strncpy(*beforeUnderscore, input, beforeLength);
        (*beforeUnderscore)[beforeLength] = '\0';

        *afterUnderscore = strdup(underscorePos);
    } else {
        *beforeUnderscore = strdup(input);
        *afterUnderscore = strdup("");
    }
}

void validatePattern(struct Expression *node) {
    if(node->symbol==""){
        return;
    }
    if (strlen(node->symbol) > 0 && node->symbol[strlen(node->symbol) - 1] == '_') {


        char *beforeUnderscore;
        char *afterUnderscore;

        separateString(node->symbol, &beforeUnderscore, &afterUnderscore);

        node->children = malloc(sizeof(Expression) * 2);
        node->numChildren = 2;
        node->children[0] = *createNode(beforeUnderscore);
        node->children[1] = *createNode(afterUnderscore);
        node->symbol = "Pattern";

    } else {
        for (int i = 0; i < node->numChildren; i++) {
            validatePattern(&node->children[i]);
        }
    }
}

char *removeUnusedSymbols(char *expr) {

    int i = 0, j = 0;
    char *result = malloc(strlen(expr) + 1);

    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (expr[i] != '\0') {
        if (expr[i] != ' ') {
            result[j] = expr[i];
            j++;
        }
        i++;
    }

    result[j] = '\0';
    return result;
}

struct Expression *parseExpression(char **expr) {
    char name[50] = {};
    if (sscanf(*expr, "%49[^[]", name) != 1) {
        fprintf(stderr, "Error while trying receive head\n");
        exit(EXIT_FAILURE);
    }
    if(strlen(*expr) != strlen(name) && (*expr)[strlen(*expr) - 1]!=']'){
        fprintf(stderr, "parentheses error, no ]\n");
        exit(EXIT_FAILURE);
    }
    // оставляем место еще на \0
    char *subString = malloc(strlen(*expr) - strlen(name) - 1);

    if (subString == NULL) {
        return createNode(*expr);
    }
    substring(*expr, subString, strlen(name) + 1, strlen(*expr) - 2 - strlen(name));

    Expression *node = createNode(name);
    if(strlen(subString)==0){
        addChild(node, createNode(subString));
    }
    for (int i = 0; i < strlen(subString); i++) {
        int d = 0;
        char symbol;
        int index = 0;
        size_t bufferSize = 10;

        char *child = (char *) malloc(bufferSize * sizeof(char));

        while (isChild(subString[i], d)) {
            symbol = subString[i];
            if (symbol == '[') d++;
            if (symbol == ']') d--;
            if (d < 0) {
                fprintf(stderr, "parentheses error\n");
                exit(EXIT_FAILURE);
            }
            if (index == bufferSize - 1) {
                bufferSize *= 2;  // Double the buffer size
                child = realloc(child, bufferSize * sizeof(char));

                if (child == NULL) {
                    fprintf(stderr, "Memory reallocation error\n");
                    freeExpression(node);
                    exit(EXIT_FAILURE);
                }
            }

            child[index++] = symbol;
            i++;
        }
        if (d != 0) {
            freeExpression(node);
            fprintf(stderr, "parentheses error\n");
            exit(EXIT_FAILURE);
        }
        if (index == bufferSize - 1) {
            bufferSize *= 2;  // Double the buffer size
            child = realloc(child, bufferSize * sizeof(char));
            if (child == NULL) {
                freeExpression(node);
                fprintf(stderr, "Memory reallocation error\n");
                exit(EXIT_FAILURE);
                return NULL;  // Exit with an error code
            }
        }

        if (index == bufferSize - 1) {
            bufferSize *= 2;  // Double the buffer size
            child = realloc(child, bufferSize * sizeof(char));

            if (child == NULL) {
                fprintf(stderr, "Memory reallocation error\n");
                freeExpression(node);
                exit(EXIT_FAILURE);
            }
        }
        child[index++] = '\0';

        addChild(node, parseExpression(&child));
        free(child);
    }
    free(subString);
    return node;
}

struct Expression *parseInput(char **expr) {
    char *filtered = removeUnusedSymbols(*expr);
    struct Expression *node = parseExpression(&filtered);
    free(filtered);
    validatePattern(node);
    return node;
}