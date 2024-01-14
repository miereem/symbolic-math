#include "solver.h"
#include "stdlib.h"
#include "transformer.h"
#include "graph.h"
#include "parser.h"

int main() {
    initContext();

    char *fib = "seq[set[f[0],0],set[f[1],1],set[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";


    char *If = "seq[setDelayed[if[true,t_,e_],t],setDelayed[if[false,t_,e_],e],addAttrs[if,holdRest]]";
    char *der0 = "seq[setDelayed[d[p_],if[numberQ[p],0,1]],set[d[sin[p_]],cos[p]]]";
    char *der1 = "seq[set[d[cos[p_]],mul[sin[p],-1]]]";
    char *der2 = "d[sin[x]]";
    char *der3 = "seq[setDelayed[d[sum[a_,b_]],sum[d[a],d[b]]]]";
    char *der = "d[sum[sin[x],x]]";
    solve(&If);
    solve(&der0);
    solve(&der1);
    solve(&der2);
    solve(&der3);
    solve(&der);

    char *While = "seq[setDelayed[while[true,a_,b_],a], setDelayed[while[false,a_,b_],b]]";
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
    char *input1 = "setDelayed["
                   "sinW[from_,to_],"
                   "while["
                   "less[from,to], "
                   "seq[ append[r,p[from,sin[from,10]]], sinW[sum[from,0.1],to]  ],"
                   " s[r] ]"
                   "]";
    char *input2 = "sinW[-3,3]";
    char *plotIn = "plot[s[r],400,500]";

    solve(&While);
    solve(&list);
    solve(&fact);
    solve(&pow);
    solve(&sin);
    solve(&input1);
    solve(&input2);
    solve(&plotIn);


    printContext();
    return 0;
}