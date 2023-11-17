#include "structure.h"
#include "derivative.h"
#include "derivetive_operation.c"
#include "creator.c"

void derivative(ExpressionNode *expressionTree) {
    derivateExpression(expressionTree);
}

ExpressionNode *derivateExpression(ExpressionNode *expressionNode) {
    if (expressionNode->type == NUMBER) {
        expressionNode->operand = 0;
    } else if (expressionNode->type == VARIABLE) {
        expressionNode->type=NUMBER;
        expressionNode->operand = 1;
    } else {
        switch (expressionNode->operationType) {
            case PLUS:
                expressionNode->left = derivateExpression(expressionNode->left);
                expressionNode->right = derivateExpression(expressionNode->right);
                break;
            case MINUS:
                expressionNode->left = derivateExpression(expressionNode->left);
                expressionNode->right = derivateExpression(expressionNode->right);
                break;
            case MULTIPLICATION:
                multiplication(expressionNode);

            case DIVISION:
                division(expressionNode);
            case SIN:
                unaryDerivative(&expressionNode, sin_d);
                break;
            case COS:
                unaryDerivative(&expressionNode, cos_d);
                break;
            case TAN:
                unaryDerivative(&expressionNode, tan_d);
                break;
            case CTAN:
                unaryDerivative(&expressionNode, ctan_d);
                break;
            case POWER:
                unaryDerivative(&expressionNode, pow_d);
                break;
            case LOGARITHM:
                unaryDerivative(&expressionNode, log_d);
                break;
            case NEGATIVE:
                unaryDerivative(&expressionNode, neg_d);
                break;
        }
    }
    return expressionNode;
}

void division(ExpressionNode *expressionNode) {
    ExpressionNode *expressionMinus = createOperation(MINUS);
    ExpressionNode *expressionPower = createOperation(POWER);
    ExpressionNode *expressionML = createOperation(MULTIPLICATION);
    ExpressionNode *expressionMR = createOperation(MULTIPLICATION);

    expressionML->left = derivateExpression(makeCopy(expressionNode->left));
    expressionML->right = expressionNode->right;

    expressionMR->left = derivateExpression(makeCopy(expressionNode->right));
    expressionMR->right = expressionNode->left;

    expressionPower->left = expressionNode->right;
    expressionPower->right = createConst(2);

    expressionMinus->left = expressionML;
    expressionMinus->right = expressionMR;

    expressionNode->operationType = DIVISION;
    expressionNode->left = expressionMinus;
    expressionNode->right = expressionPower;
}

void multiplication(ExpressionNode *expressionNode) {

    ExpressionNode *expressionML = createOperation(MULTIPLICATION);
    ExpressionNode *expressionMR = createOperation(MULTIPLICATION);

    expressionML->left = derivateExpression(makeCopy(expressionNode->left));
    expressionML->right = expressionNode->right;

    expressionMR->left = derivateExpression(makeCopy(expressionNode->right));
    expressionMR->right = expressionNode->left;

    expressionNode->operationType = PLUS;
    expressionNode->left = expressionML;
    expressionNode->right = expressionMR;
}

void unaryDerivative(ExpressionNode **expressionNode, ExpressionNode *(*dirative)(ExpressionNode *)) {
    ExpressionNode *expressionNodeMain = createOperation(MULTIPLICATION);
    ExpressionNode *copyLeftNode = makeCopy((*expressionNode)->left);
    ExpressionNode * left = (*dirative)(*expressionNode);
    ExpressionNode * right = derivateExpression(copyLeftNode);
    expressionNodeMain->left = left;
    expressionNodeMain->right = right;

    *expressionNode = expressionNodeMain;
}


