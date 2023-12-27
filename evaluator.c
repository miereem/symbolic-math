#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "structures.h"
#include "transformer.h"

struct Expression *sum(struct Expression *node) {
    int sum = 0;
    struct Expression *res = createNode(node->symbol);
    if (node->numChildren > 0) {
        for (int i = 0; i < node->numChildren; i++) {
            if (isdigit(node->children[i].symbol[0])) {
                sum += atoi(node->children[i].symbol);
            } else {
                addChild(res, createNode(node->children[i].symbol));
            }
        }
    }
    size_t size = sizeof(sum);
    char symbol[size];
    sprintf(symbol, "%d", sum);
    // itoa(sum, symbol[size], 10);
    if (res->numChildren == 0) {
        return createNode(symbol);
    } else {
        addChild(res, createNode(symbol));
    }
    return res;
}

struct Expression *mul(struct Expression *node) {
    int mul = 1;
    struct Expression *res = createNode(node->symbol);
    if (node->numChildren > 0) {
        for (int i = 0; i < node->numChildren; i++) {
            if (isdigit(node->children[i].symbol[0])) {
                mul *= atoi(node->children[i].symbol);
            } else {
                addChild(res, createNode(node->children[i].symbol));
            }
        }
    }
    size_t size = sizeof(mul);
    char symbol[size];
    sprintf(symbol, "%d", mul);
    // itoa(mul, symbol[size], 10);
    if (res->numChildren == 0) {
        return createNode(symbol);
    } else {
        addChild(res, createNode(symbol));
    }
    return res;
}

//struct Expression *div(struct Expression *node) {
//    int div = atoi(node->children[0].symbol);
//    struct Expression *res = createNode(node->symbol);
//    if (node->numChildren > 0) {
//        for (int i = 1; i < node->numChildren; i++) {
//            if (isdigit(node->children[i].symbol[0])) {
//                div /= atoi(node->children[i].symbol);
//            } else {
//                addChild(res, createNode(node->children[i].symbol));
//            }
//        }
//    }
//    size_t size = sizeof(mul);
//    char symbol[size];
//    sprintf(symbol, "%d", mul);
//    // itoa(mul, symbol[size], 10);
//    if (res->numChildren == 0) {
//        return createNode(symbol);
//    } else {
//        addChild(res, createNode(symbol));
//    }
//    return res;
//}
