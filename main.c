#include "solver.h"
#include "transformer.h"

int main() {

//     char *input = "seq[set[d[p_],0],set[pow[n_,x_],mul[n,n]],setDelayed[d[pow[x_,n_]],mul[n,pow[x,sum[n,-1]]]],pow[5,2],d[1]]";
//     char *input1 = "d[pow[5,2]]";
    char *fib = "seq[set[f[0],0],set[f[1],1],set[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";

    char *If = "seq[setDelayed[if[true,t_,e_],t],setDelayed[if[false,t_,e_],e],]";
    char *While = "setDelayed[f[x_],if[less[x,3],1,sum[f[sum[x,-1]],f[sum[x,-2]]]]]";

    char *input = "f[5]";

    initContext();
    solve(&fib);
    solve(&If);
    solve(&While);
    solve(&input);
    printContext();
    return 0;
}