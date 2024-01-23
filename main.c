#include "solver.h"
#include "stdlib.h"
#include "transformer.h"
#include "graph.h"
#include "parser.h"

int main() {

    initContext();

    char *Const = "seq[set[const,0]]";
    char * list = "setDelayed[r,l[]]";
    char *If = "seq[setDelayed[if[true,t_,e_],t],setDelayed[if[false,t_,e_],e],addAttrs[if,holdRest]]";
    char *While = "seq[setDelayed[while[c_,b_],if[c,seq[b,while[c, b]],null]],addAttrs[while,holdAll]]";
    char* main = "while[less[const,3],set[const,sum[const,1]]]";
    char* check = "const";


    solve(&If);
    solve(&Const);


    solve(&While);
    solve(&main);

    solve(&check);


    printContext();
    return 0;
}
