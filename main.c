#include "solver.h"
#include "stdlib.h"
#include "transformer.h"
#include "graph.h"
#include "parser.h"

int main() {

    char *fib = "seq[set[f[0],0],set[f[1],1],set[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";

    char *If = "seq[setDelayed[if[true,t_,e_],t],setDelayed[if[false,t_,e_],e],addAttrs[if,holdRest]]";
    char *While = "setDelayed[f[x_],if[less[x,3],1,sum[f[sum[x,-1]],f[sum[x,-2]]]]]";

    char *input = "f[5]";
    char *der = "seq[set[d[p_],0],set[d[sin[p_]],cos[p]]]";
    char *der0 = "seq[set[d[p_],0],set[d[cos[p_]],sum[sin[p],-1]]]";
    char *der1 = "d[sin[x]]";
    char *plotIn = "plot[s[l[p[1,2], p[2,7]], l[p[1,5],p[6,7]], l[p[2,3], p[6,27]]],400,500]";

    initContext();
    solve(&fib);
    solve(&If);
    solve(&While);
    solve(&input);
    solve(&der);
    solve(&der1);
    printContext();
    return 0;
}