#include "solver.h"
#include "transformer.h"

int main() {

    //char *input = "seq[set[f[0],0],set[f[1],1],s e t[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";
    char *input = "seq[set[if[true,f_,r_],f],set[if[false,f_,r_],r]]";
    char *input1 = "if[less[8,9],8,9]";
    initContext();
    solve(&input);
    solve(&input1);

    printContext();

    return 0;
}
