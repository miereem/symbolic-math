#include "solver.h"
#include "stdlib.h"
#include "transformer.h"
#include "graph.h"
#include "parser.h"

int main() {

    char *fib = "seq[set[f[0],0],set[f[1],1],set[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";

    char *If = "seq[setDelayed[if[true,t_,e_],t],setDelayed[if[false,t_,e_],e],addAttrs[if,holdRest]]";
    char *While = "setDelayed[f[x_],if[less[x,3],1,sum[f[sum[x,-1]],f[sum[x,-2]]]]]";

//    char *input = "numberQ[sum[9,5]]";
    char *der4 = "seq[setDelayed[d[p_],if[numberQ[p],0,1]],set[d[sin[p_]],cos[p]]]";

    char *der = "seq[set[d[sin[p_]],cos[p]]]";
    char *der0 = "seq[set[d[cos[p_]],mul[sin[p],-1]]]";
    char *der1 = "d[sin[x]]";
    char *der2 = "seq[setDelayed[d[sum[a_,b_]],sum[d[a],d[b]]]]";
    char *der3 = "d[sum[sin[x],x]]";


    char *list = "set[r,l[]]";
    char *fact = "seq[set[fac[1.], 1], setDelayed[fac[p_],mul[p, fac[sum[p,-1]]]]]";
    char *pow = "seq[set[pow[p_,1.],p], setDelayed[pow[p_,k_],mul[p,pow[p,sum[k,-1]]]]]";
    char *sin = "seq[setDelayed[sin[z_,0.], z],"
                "setDelayed[sin[z_,k_], sum["
                "mul["
                "pow[-1,k],"
                "div["
                "pow[z, sum[1,mul[2,k]]],"
                "fac[sum[1,mul[2,k]]]"
                "]]"
                ", sin[z, sum[k,-1]]"
                "]"
                "]"
                "]";
    char *input1 = "append[r,p[0.1,sin[0.1,10]]]";
    char *input2 = "p[0.1,sin[0.1,10]]";
    char *input3 = "r";

    char *plotIn = "plot[s[l[p[1,2], p[2,7]], l[p[1,5],p[6,7]], l[p[2,3], p[6,27]]],400,500]";

    initContext();
//    solve(&fib);
//    solve(&If);
//    solve(&While);
    solve(&list);
    solve(&fact);
    solve(&pow);
    solve(&sin);
    solve(&input1);
    solve(&input2);
    solve(&input3);

//    solve(&der);
//    solve(&der0);
//
//    solve(&der1);
//    solve(&der2);
//    solve(&der4);
//
//    solve(&der3);


    printContext();
    return 0;
}