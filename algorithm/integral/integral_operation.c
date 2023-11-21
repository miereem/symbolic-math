#include "integral_operation.h"
#include "../creator.h"
#include <stdbool.h>
#include <stdlib.h>

bool isIntegralType1(ExpressionNode *node) {
    return
            node->operationType == POWER
            && node->left->type == VARIABLE
            && node->left->op == 'x'
            && node->right->type == VARIABLE;
}

ExpressionNode *getIntegralType1(ExpressionNode *node) {
    ExpressionNode *division = createOperation(DIVISION);
    division->left = node;
    ExpressionNode *plus = createOperation(PLUS);
    plus->left = node->right;
    plus->right = createConst(1);
    node->right = plus;
    division->right = plus;
    return division;
}

bool isIntegralType2(ExpressionNode *node) {
    return
            node->operationType == POWER
            && node->left->type == VARIABLE
            && node->left->op == 'e'
            && node->right->type == VARIABLE
            && node->right->op == 'x';
}

ExpressionNode *getIntegralType2(ExpressionNode *node) {
    return node;
}

bool isIntegralType3(ExpressionNode *node) {
    return
            node->operationType == SIN
            && node->left->type == VARIABLE
            && node->left->op == 'x';
}

ExpressionNode *getIntegralType3(ExpressionNode *node) {
    ExpressionNode *neg = createOperation(NEGATIVE);
    neg->left = node;
    node->operationType = COS;
    return neg;
}

bool isIntegralType4(ExpressionNode *node) {
    return
            node->operationType == DIVISION
            && node->left->type == NUMBER
            && node->left->operand == 1
            && node->right->operationType == POWER
            && node->right->left->operationType == COS
            && node->right->left->left->type == VARIABLE
            && node->right->left->left->op == 'x'
            && node->right->right->type == NUMBER
            && node->right->right->operand == 2;
}

ExpressionNode *getIntegralType4(ExpressionNode *node) {
    free(node);
    ExpressionNode *tan = createOperation(TAN);
    tan->left = createVariable('x');
    return tan;
}

bool isIntegralType5(ExpressionNode *node) {
    return
            node->operationType == DIVISION
            && node->left->type == NUMBER
            && node->left->operand == 1
            && node->right->operationType == PLUS
            && node->right->left->operationType == POWER
            && node->right->left->left->type == VARIABLE
            && node->right->left->left->op == 'x'
            && node->right->left->right->type == NUMBER
            && node->right->left->right->operand == 2
            && node->right->right->operationType == POWER
            && node->right->right->left->type == VARIABLE
            && node->right->right->left->op != 'x'
            && node->right->right->right->type == NUMBER
            && node->right->right->right->operand == 2;
}

ExpressionNode *getIntegralType5(ExpressionNode *node) {
    char var = node->right->right->left->op;
    free(node);
    ExpressionNode *mul = createOperation(MULTIPLICATION);

    ExpressionNode *div = createOperation(DIVISION);
    div->left = createConst(1);
    div->right = createVariable(var);
    mul->left = div;

    ExpressionNode *atan = createOperation(ATAN);
    ExpressionNode *atan_div = createOperation(DIVISION);
    atan_div->left = createVariable('x');
    atan_div->right = createVariable(var);
    atan->left = atan_div;

    mul->right = atan;
    return mul;
}

bool isIntegralType6(ExpressionNode *node) {
    return
            node->operationType == DIVISION
            && node->left->type == NUMBER
            && node->left->operand == 1
            && node->right->operationType == POWER

            && node->right->left->operationType == MINUS

            && node->right->left->left->operationType == POWER
            && node->right->left->left->left->type == VARIABLE
            && node->right->left->left->left->op != 'x'
            && node->right->left->left->right->type == NUMBER
            && node->right->left->left->right->operand == 2


            && node->right->left->right->operationType == POWER
            && node->right->left->right->left->type == VARIABLE
            && node->right->left->right->left->op == 'x'
            && node->right->left->right->right->type == NUMBER
            && node->right->left->right->right->operand == 2

            && node->right->right->operationType == DIVISION
            && node->right->right->left->type == NUMBER
            && node->right->right->left->operand == 1
            && node->right->right->right->type == NUMBER
            && node->right->right->right->operand == 2;
}

ExpressionNode *getIntegralType6(ExpressionNode *node) {
    char var = node->right->right->right->right->op;
    free(node);
    ExpressionNode *asin = createOperation(ASIN);
    ExpressionNode *atan_div = createOperation(DIVISION);
    atan_div->left = createVariable('x');
    atan_div->right = createVariable(var);
    asin->left = atan_div;

    return asin;
}
bool isIntegralType7(ExpressionNode *node) {
    node->operationType == DIVISION
    && node->left->type == NUMBER
    && node->left->operand == 1
    && node->right->operationType == POWER

    && (node->right->left->operationType == PLUS || node->right->left->operationType==MINUS)

    && node->right->left->left->operationType == POWER
    && node->right->left->left->left->type == VARIABLE
    && node->right->left->left->left->op != 'x'
    && node->right->left->left->right->type == NUMBER
    && node->right->left->left->right->operand == 2


    && node->right->left->right->operationType == POWER
    && node->right->left->right->left->type == VARIABLE
    && node->right->left->right->left->op == 'x'
    && node->right->left->right->right->type == NUMBER
    && node->right->left->right->right->operand == 2

    && node->right->right->operationType == DIVISION
    && node->right->right->left->type == NUMBER
    && node->right->right->left->operand == 1
    && node->right->right->right->type == NUMBER
    && node->right->right->right->operand == 2;
}

ExpressionNode *getIntegralType7(ExpressionNode *node) {
    node->operationType=LOGARITHM;
    ExpressionNode * mod = createOperation(MODULE);
    ExpressionNode * plus = createOperation(PLUS);
    plus->left= createVariable('x');
    plus->right=node->left;

    mod->left=plus;
    node->left= createVariable('e');
    node->right=mod;

    return node;
}
bool isIntegralType8(ExpressionNode *node) {
    return
            node->operationType == DIVISION
            && node->left->type == NUMBER
            && node->left->operand==1
            && node->right->type==VARIABLE
            && node->right->op == 'x';
}

ExpressionNode *getIntegralType8(ExpressionNode *node) {
    free(node);
    ExpressionNode *log = createOperation(LOGARITHM);
    log->left= createVariable('e');

    ExpressionNode * mod = createOperation(MODULE);
    mod->left= createVariable('x');
    log->right=mod;
    return log;
}

bool isIntegralType9(ExpressionNode *node) {
    return
            node->operationType == POWER
            && node->left->type == VARIABLE
            && node->left->operand!='x'
            && node->right->type==VARIABLE
            && node->right->op == 'x';
}

ExpressionNode *getIntegralType9(ExpressionNode *node) {
    char var = node->left->op;
    ExpressionNode *div = createOperation(DIVISION);
    div->left=node;
    ExpressionNode * log = createOperation(LOGARITHM);
    log->left= createVariable('e');
    log->right= createVariable(var);
    div->right=log;
    return div;
}
bool isIntegralType10(ExpressionNode *node) {
    return
            node->operationType == COS
            && node->left->type == VARIABLE
            && node->left->op == 'x';
}

ExpressionNode *getIntegralType10(ExpressionNode *node) {
    node->operationType = SIN;
    return node;
}

bool isIntegralType11(ExpressionNode *node) {
    return
            node->operationType == DIVISION
            && node->left->type == NUMBER
            && node->left->operand == 1
            && node->right->operationType == POWER
            && node->right->left->operationType == SIN
            && node->right->left->left->type == VARIABLE
            && node->right->left->left->op == 'x'
            && node->right->right->type == NUMBER
            && node->right->right->operand == 2;
}

ExpressionNode *getIntegralType11(ExpressionNode *node) {
    free(node);
    ExpressionNode * neg = createOperation(NEGATIVE);
    ExpressionNode *ctan = createOperation(CTAN);
    ctan->left = createVariable('x');
    neg->left=ctan;
    return neg;
}
bool isIntegralType12(ExpressionNode *node) {
    return
            node->operationType == DIVISION
            && node->left->type == NUMBER
            && node->left->operand == 1
            && node->right->operationType == MINUS
            && node->right->left->operationType == POWER
            && node->right->left->left->type == VARIABLE
            && node->right->left->left->op == 'x'
            && node->right->left->right->type == NUMBER
            && node->right->left->right->operand == 2
            && node->right->right->operationType == POWER
            && node->right->right->left->type == VARIABLE
            && node->right->right->left->op != 'x'
            && node->right->right->right->type == NUMBER
            && node->right->right->right->operand == 2;
}

ExpressionNode *getIntegralType12(ExpressionNode *node) {
    char var = node->right->right->left->op;
    free(node);
    ExpressionNode * mul = createOperation(MULTIPLICATION);

    ExpressionNode * div = createOperation(DIVISION);
    div->left= createConst(1);
    ExpressionNode * mul2a = createOperation(MULTIPLICATION);
    mul2a->left= createConst(2);
    mul2a->right= createVariable(var);
    div->right=mul2a;
    mul->left=div;

    ExpressionNode * mod = createOperation(MODULE);
    ExpressionNode * mod_div = createOperation(DIVISION);
    ExpressionNode * mod_div_min = createOperation(MINUS);
    mod_div_min->left= createVariable('x');
    mod_div_min->right= createVariable(var);
    ExpressionNode * mod_div_pl = createOperation(PLUS);
    mod_div_pl->left= createVariable('x');
    mod_div_pl->right= createVariable('a');
    mod_div->left=mod_div_min;
    mod_div->right=mod_div_pl;

    mod->left=mod_div;
    mul->right=mod;
    return mul;
}