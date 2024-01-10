//
// Created by Home on 22.12.2023.
//

#ifndef SYMBOLIC_PARSER_H
#define SYMBOLIC_PARSER_H
#include "structures.h"
struct Expression *parseInput(char **expr);
struct PlotDTO * parsePLot(Expression *expression);
#endif //SYMBOLIC_PARSER_H