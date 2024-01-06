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
    // Find the position of the first underscore
    const char *underscorePos = strchr(input, '_');

    // Check if underscore is found
    if (underscorePos != NULL) {
        // Calculate the length before the underscore
        size_t beforeLength = underscorePos - input;

        // Allocate memory for the "before" string and copy it
        *beforeUnderscore = malloc(beforeLength + 1);
        strncpy(*beforeUnderscore, input, beforeLength);
        (*beforeUnderscore)[beforeLength] = '\0';

        // Allocate memory for the "after" string and copy it
        *afterUnderscore = strdup(underscorePos);
    } else {
        // If underscore is not found, set "before" to the entire input and "after" to an empty string
        *beforeUnderscore = strdup(input);
        *afterUnderscore = strdup("");
    }
}
void validatePattern(struct Expression* node){
    if (strcmp(node->symbol, "pattern") == 0) {
        // Code for handling the "pattern" case
    }

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
struct Expression *parseExpression(char **expr) {
    char name[50] = {};

    if (sscanf(*expr, "%49[^[]", name) != 1) {
        return NULL;
    }
//    if(name[0]=='-'){
//        Expression *node = createNode("sub");
//        addChild(node, createNode("0"));
//        addChild(node, parseExpression(&child));
//    }
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
            if(d<0) return NULL;
            if (index == bufferSize - 1) {
                bufferSize *= 2;  // Double the buffer size
                child = realloc(child, bufferSize * sizeof(char));

                if (child == NULL) {
                    fprintf(stderr, "Memory reallocation error\n");
                    freeExpression(node);
                    return NULL;  // Exit with an error code
                }
            }

            child[index++] = symbol;
            i++;
        }
        if(d!=0){
            freeExpression(node);
            return NULL;
        }
        if (index == bufferSize - 1) {
            bufferSize *= 2;  // Double the buffer size
            child = realloc(child, bufferSize * sizeof(char));
            if (child == NULL) {
                freeExpression(node);
                fprintf(stderr, "Memory reallocation error\n");
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
    struct Expression * node = parseExpression(expr);
    validatePattern(node);
    return node;
}