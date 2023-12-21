#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structures.h"

//void set(char *expr) {
//    char name[100];
//    char trans[100];
//    printf("%s ", expr);
//
//    sscanf(expr, "%99[^,]", name);
//    sscanf(expr, "%*[^,]%99[^\n]", trans);
//    context.names[context.numNames] = strdup(name);
//    printf("%s ", name);
//
//    printf("%s ", context.names[context.numNames]);
//
//    if (context.names[context.numNames] != NULL) {
//        context.numNames++;
//    } else {
//        printf("Memory allocation error\n");
//    }
//}

void substring(char *s, char *sub, int p, int l) {
    int c = 0;

    while (c < l) {
        *(sub + c) = *(s + (p + c));
        c++;
    }
    sub[c] = '\0';
}

bool isChild(char s, int d) {
    if (s == ',' && d == 0 || s == '\0') {
        return false;
    }
    return true;
}

struct Expression *parseExpression(char **expr) {
    char name[50] = {};

    if (sscanf(*expr, "%49[^[]", name) != 1) {
        return NULL;
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

            // Check if the buffer is full and resize if necessary
            if (index == bufferSize - 1) {
                bufferSize *= 2;  // Double the buffer size
                child = realloc(child, bufferSize * sizeof(char));

                if (child == NULL) {
                    fprintf(stderr, "Memory reallocation error\n");
                    return NULL;  // Exit with an error code
                }
            }

            child[index++] = symbol;
            i++;
        }
        if (index == bufferSize - 1) {
            bufferSize *= 2;  // Double the buffer size
            child = realloc(child, bufferSize * sizeof(char));

            if (child == NULL) {
                fprintf(stderr, "Memory reallocation error\n");
                return NULL;  // Exit with an error code
            }
        }

        child[index++] = '\0';

        addChild(node, parseExpression(&child));
        free(child);
    }
//    free(subString);

    return node;
}
