#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"


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
void validatePattern(struct Expression* node){
    if (strlen(node->symbol) > 0 && node->symbol[strlen(node->symbol) - 1] == '_') {


        char *beforeUnderscore;
        char *afterUnderscore;

        separateString(node->symbol, &beforeUnderscore, &afterUnderscore);

        node->children=malloc(sizeof(Expression)*2);
        node->numChildren=2;
        node->children[0]= *createNode(beforeUnderscore);
        node->children[1]=*createNode(afterUnderscore);
        node->symbol= "Pattern";

    }
    else {
        for (int i = 0; i < node->numChildren; i++) {
            validatePattern(&node->children[i]);
        }
    }
}
char * removeUnusedSymbols(char *expr) {

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
    char *subString = malloc(strlen(*expr) - strlen(name) - 2);

    if (subString == NULL) {
        return createNode(*expr);
    }
    substring(*expr, subString, strlen(name) + 1, strlen(*expr) - 2 - strlen(name));

    Expression *node = createNode(name);

    for (int i = 0; i < strlen(subString); i++) {
        int d = 0;
        char symbol;
        int index = 0;
        size_t bufferSize = 10;

        char *child = (char *) malloc(bufferSize * sizeof(char));

        while (isChild(symbol = subString[i], d)) {
            if (symbol == '[') d++;
            if (symbol == ']') d--;
            if(d<0) {
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
        if(d!=0){
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

        child[index++] = '\0';

        addChild(node, parseExpression(&child));
        free(child);
    }
    free(subString);
    return node;
}
struct Expression * parseInput(char **expr){
    char * filtered  = removeUnusedSymbols(*expr);
    struct Expression * node = parseExpression(&filtered);
    free(filtered);
    validatePattern(node);
    return node;
}