#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "util.h"
#include "transformer.h"

struct Expression *sum(struct Expression *node) {
    double sum = 0;
    double current;
    struct Expression *res = createNode(node->symbol);
    if (node->numChildren > 0) {
        for (int i = 0; i < node->numChildren; i++) {
            if ((isdigit(node->children[i].symbol[0])) != 0 || node->children[i].symbol[0] == '-') {
                current = atof(node->children[i].symbol);
                sum += current;
            } else {
                addChild(res, &node->children[i]);
            }
        }
    }

//    char symbol[100];
//    sprintf(symbol, "%.20f", sum);
    char symbol[100];
    gcvt(sum, 5, symbol);
    if (res->numChildren == 0) {
        freeExpression(res);
        return createNode(symbol);
    } else {
        if (strcmp(symbol, "0") != 0) {
            addChild(res, createNode(symbol));
        } else if (res->numChildren == 1) {
            res = &res->children[0];
        }
    }
    return res;
}

struct Expression *less(struct Expression *node) {
    if (node->numChildren != 2) {
        return copyNode(node);
    }
    if (((isdigit(node->children[0].symbol[0])) != 0 || node->children[0].symbol[0] == '-') && ((isdigit(node->children[1].symbol[0])) != 0 || node->children[1].symbol[0] == '-') ) {
        double first = atof(node->children[0].symbol);
        double second = atof(node->children[1].symbol);
        if (first >= second) {
            return createNode("false");
        }
        return createNode("true");
    } else return copyNode(node);
}
struct Expression *more(struct Expression *node) {
    if (node->numChildren != 2) {
        return copyNode(node);
    }
    if (((isdigit(node->children[0].symbol[0])) != 0 || node->children[0].symbol[0] == '-') && ((isdigit(node->children[1].symbol[0])) != 0 || node->children[1].symbol[0] == '-') ) {
        double first = atof(node->children[0].symbol);
        double second = atof(node->children[1].symbol);
        if (first <= second) {
            return createNode("false");
        }
        return createNode("true");
    } else return copyNode(node);
}
struct Expression *eq(struct Expression *node) {
    if (node->numChildren != 2) {
        return copyNode(node);
    }
    if (((isdigit(node->children[0].symbol[0])) != 0 || node->children[0].symbol[0] == '-') && ((isdigit(node->children[1].symbol[0])) != 0 || node->children[1].symbol[0] == '-') ) {
        double first = atof(node->children[0].symbol);
        double second = atof(node->children[1].symbol);
        if (first != second) {
            return createNode("false");
        }
        return createNode("true");
    } else return copyNode(node);
}


struct Expression *mul(struct Expression *node) {
    double mul = 1;
    struct Expression *res = createNode(node->symbol);
    if (node->numChildren > 0) {
        for (int i = 0; i < node->numChildren; i++) {
            if (isdigit(node->children[i].symbol[0]) || node->children[i].symbol[0]=='-') {
                mul *= atof(node->children[i].symbol);
            } else {
                addChild(res, &node->children[i]);
            }
        }
    }

    char symbol[100];
    gcvt(mul, 5, symbol);

//    sprintf(symbol, "%.20f", mul);
    // itoa(mul, symbol[size], 10);
    if (res->numChildren == 0) {
        return createNode(symbol);
    } else {
        if (strcmp(symbol, "1") != 0) {
            addChild(res, createNode(symbol));
        } else return res;
    }
    return res;
}


struct Expression *numberQ(struct Expression *node) {
    if (node->numChildren != 1) {
        return node;
    }
    if ((isdigit(node->children[0].symbol[0])) != 0 || node->children[0].symbol[0] == '-') {
        return createNode("true");
    }
    return createNode("false");
}



struct Expression *divide(struct Expression *node) {
    if (node->numChildren == 0) {
        return node;
    }
    if (strcmp(node->children[0].symbol,node->children[1].symbol) == 0) {
        return createNode("1");
    }
    if (strcmp(node->children[1].symbol,"1") == 0) {
        return createNode(node->children[0].symbol);
    }
    double quotient = 0;
    if ((isdigit(node->children[0].symbol[0])) != 0 || node->children[0].symbol[0] == '-') {
         quotient = atof(node->children[0].symbol);
    } else return copyNode(node);

    if ((isdigit(node->children[1].symbol[0])) == 0 && node->children[1].symbol[0] != '-') {
      return copyNode(node); }

    struct Expression *res = createNode(node->symbol);

    for (int i = 1; i < node->numChildren; i++) {
        if (isdigit(node->children[i].symbol[0]) && atof(node->children[i].symbol) != 0) {
            quotient /= atof(node->children[i].symbol);
        } else {
            addChild(res, &node->children[i]);
        }
    }


//    char symbol[100];
//    sprintf(symbol, "%.20f", quotient);
    char symbol[100];
    gcvt(quotient, 5, symbol);
    if (res->numChildren == 0) {
        return createNode(symbol);
    } else {
        if (strcmp(symbol, "1") != 0) {
            addChild(res, createNode(symbol));
        } else return res;
    }

    return res;
}




