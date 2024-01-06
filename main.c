#include "solver.h"
#include "transformer.h"

int main() {
//    char *input = "set[f[5],sum[1,5]]";
    char *input = "set[f[4],0]";
    char *input1 = "set[f[5],1]";
    char *input2 = "set[f[6],2]";
    char *input3 = "set[f[n_], sum[f[sum[n,1]], f[sum[n,2]]]]";
    char *input4 = "f[3]";
//    char *input4 = "sum[hold[f[20],f[9]],6]";
//    char *input5 = "set[f[20],6]";
//    char *input6 = "addAttrs[f,holdAll]";
//    char *input7 = "f[g[7],g[9]]";
//    char *input8 = "mul[sum[7,1],9]";


    initContext();

//    solve(&input);
    solve(&input);
    solve(&input1);
    solve(&input2);
    solve(&input3);
    solve(&input4);
//    solve(&input3);
//    solve(&input5);
//    solve(&input4);

//    solve(&input7);


    printContext();

    return 0;
}
