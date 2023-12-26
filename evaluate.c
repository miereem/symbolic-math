

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "structures.h"

struct Expression* sum(struct Expression* node) {
    int sum = 0;
    struct Expression* res = createNode(node->symbol);
    if (node->numChildren > 0) {
        for (int i = 0; i < node->numChildren; i++) {
            if (isdigit(node->children[i].symbol[0])) {
                sum += atoi(node->children[i].symbol);
            } else {
                addChild(res,createNode(node->children[i].symbol));
            }

        }

    }
    char symbol[6];
    itoa(sum, symbol, 10);
    if (res->numChildren == 0) {
        return createNode(symbol);
    } else {
        addChild(res,createNode(symbol));
    }
    return res;
}