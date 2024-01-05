#include "solver.h"
#include "transformer.h"

int main() {
    char *input = "set[f[5],sum[1,5]]";
    char *input2 = "set[f[n_,m_],mul[sum[n,n],m]]";
    char *input3 = "setDelayed[f[p_],sum[p,9,9,8]]";
    char *input4 = "sum[hold[f[20],f[9]],6]";
    char *input5 = "set[f[20],6]";
    char *input6 = "addAttrs[f,holdFirst]";
    char *input7 = "f[f[7],f[9]]";
    char *input8 = "mul[sum[7,1],9]";


    initContext();

    solve(&input);
    solve(&input2);
    solve(&input6);
    solve(&input3);
    solve(&input5);
    solve(&input4);

    solve(&input7);


    printContext();

    return 0;
}
