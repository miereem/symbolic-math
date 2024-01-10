#include "solver.h"
#include "transformer.h"

int main() {

   // char *input = "seq[set[f[0],0],set[f[1],1],s e t[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";
    char *input = "set[f[a_,b_,c_,d_,e_],sum[a,b,c,d,e]]";
    char *input1 = "f[less[8,1],1,2,3,4]";

    initContext();
    solve(&input);
    solve(&input1);


    printContext();

    return 0;
}
