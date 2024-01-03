#include "solver.h"
#include "transformer.h"

int main() {
    char *input = "set[f[5],1]";
    char *input2 = "set[f[n_,m_],mul[sum[n,n],m]]";
    char *input3 = "set[f[p_],sum[p,9]]";
    char *input4 = "sum[hold[f[20]],6]";
    char *input5 = "set[f[20],6]";
    char *input6 = "mul[f[20],6]";


    initContext();

    solve(&input);
    solve(&input3);
    solve(&input5);
    solve(&input4);
    solve(&input6);



    return 0;
}
