//#include "solver.h"
//#include "transformer.h"
//
//int main() {
////    char *input = "set[f[5],sum[1,5]]";
//    char *input2 = "set[f[n_,m_],sum[n,m]]";
//    char *input3 = "set[g[p_],sum[p,9]]";
////    char *input4 = "sum[hold[f[20],f[9]],6]";
////    char *input5 = "set[f[20],6]";
//    char *input6 = "addAttrs[f,holdFirst]";
//    char *input7 = "f[g[7],g[9]]";
//    //char *input7 = "mul[g[7],0]";
//
////    char *input8 = "mul[sum[7,1],9]";
//
//
//    initContext();
//
////    solve(&input);
//    solve(&input2);
//    solve(&input6);
//    solve(&input3);
////    solve(&input5);
////    solve(&input4);
//
//    solve(&input7);
//
//
//    printContext();
//
//    return 0;
//}
#include "solver.h"
#include "transformer.h"

int main() {
////    char *input = "set[f[5],sum[1,5]]";
//    char *input = "set[g[p_],sum[p,9]]";
//    char *input2 = "sum[g[g[g[g[k[5]]]]],6]";
////    char *input2 = "set[f[n_,m_],sum[n,m]]";
////    char *input4 = "sum[hold[f[20],f[9]],6]";
////    char *input5 = "set[f[20],6]";
////    char *input6 = "addAttrs[f,holdAll]";
////    char *input7 = "f[g[7],g[9]]";
////    char *input8 = "mul[sum[7,1],9]";

//    char *input = "set[f[7],0]";
//    char *input1 = "set[f[8],1]";
//    char *input2 = "set[f[9],2]";
//
//    char *input3 = "setDelayed[f[p_],sum[f[sum[p,1]],f[sum[p,2]]]]";
//    char *input4 = "f[3]";
    char *input = "set[g[p_],sum[p,9]]";
    char *input1 = "set[z[p_],sum[p,8]]";
    char *input2 = "set[d[g[p_]],z[p]]";
  //  char *input3 = "set[d[e_],z[e]]";
   // char *input4 = "d[g[5]]";
    char *input4 = "seq[set[d[e_],z[e]],d[g[5]]]";

    initContext();
    solve(&input);
    solve(&input1);
    solve(&input2);
  //  solve(&input3);
    solve(&input4);
//    solve(&input7);


    printContext();

    return 0;
}
