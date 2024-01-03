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
                addChild(res, &node->children[i]);
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
                addChild(res, &node->children[i]);
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

struct Expression *divide(struct Expression *node) {
    //вообще можно сделать логику: отправь всех кроме первого ребенка в mul, потом сделай div(child[0], mul(rest_children));
    if (node->numChildren > 1) {
        struct Expression *res = createNode(node->symbol);
        if (isdigit(node->children[0].symbol[0])) {
            int div = atoi(node->children[0].symbol);
            char symbol[sizeof(div)];
            sprintf(symbol, "%d", div);
            // itoa(mul, symbol[size], 10);
            addChild(res, createNode(symbol));
            if (node->numChildren > 1) {
                for (int i = 1; i < node->numChildren; i++) {
                    if (isdigit(node->children[i].symbol[0])) {
                        div /= atoi(node->children[i].symbol);
                    } else {
                        addChild(res, createNode(node->children[i].symbol));
                    }
                }
                size_t size = sizeof(div);
                char symbol[size];
                sprintf(symbol, "%d", div);
            } else {
                addChild(res, createNode(symbol));
            }
            return res;
        } else {
            addChild(res, createNode(node->children[0].symbol));
          //  addChild(mul()) //нужно отправить детей без нулевого ребенка
        }
    } else {
        return node;
    }

}

