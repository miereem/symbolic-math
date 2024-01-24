//
// Created by Home on 22.12.2023.
//

#ifndef SYMBOLIC_EVALUATOR_H
#define SYMBOLIC_EVALUATOR_H

struct Expression *sum(struct Expression *node);

struct Expression *mul(struct Expression *node);

struct Expression *less(struct Expression *node);

struct Expression *more(struct Expression *node);

struct Expression *eq(struct Expression *node);

struct Expression *numberQ(struct Expression *node);

struct Expression *divide(struct Expression *node);


#endif //SYMBOLIC_EVALUATOR_H
