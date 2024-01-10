#include "solver.h"
#include "transformer.h"

int main() {

    char *input = "seq[set[f[0],0],set[f[1],1],s e t[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";

    initContext();
    solve(&input);


    printContext();

    return 0;
}
