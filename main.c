#include "solver.h"
#include "stdlib.h"
#include "transformer.h"
#include "graph.h"
#include "parser.h"

int main() {

    initContext();

//    char *Const = "seq[set[const,0]]";
    char * list = "setDelayed[r,l[]]";
    char *If = "seq[setDelayed[if[true,t_,e_],t],setDelayed[if[false,t_,e_],e],addAttrs[if,holdRest]]";
    char *While = "seq[setDelayed[while[c_,b_],if[c,seq[b,while[c, b]],null]],addAttrs[while,holdAll]]";
    char * test = "set[r,l[l[1,2,3,4],l[2,3,4,5],l[3,4,5,6],l[4,5,6,7]]]";

    char* main = "while[less[const,3],seq[set[const,sum[const,1]],set[r,rest[r]]]]";
    char* drop = "setDelayed["
                "drop[list_],"
                "seq["
                "set[h,l[]],"
                "set[counter2,1],"
                "while["
                "less[counter2, len[list]], "
                "seq[set[m2,seq[get[list, counter2],first[m]]],set[m2,rest[m2]],append[h, m2], set[counter2, sum[counter2,1]]]"
                "]"
                "],"
                "first[m]"
                "]";

    char* get = "setDelayed["
                "get[list_,index_],"
                "seq["
                "set[m,list],"
                "set[counter,0],"
                "while["
                        "less[counter,index],"
                        "seq[set[counter,sum[counter,1]] ,set[m,rest[m]]] "
                "]"
                "]"
                "]";
    char* insert = "setDelayed["
                "insert[l_,n_,s_],"
                "seq["
                "set[m3,l[]],"
                "set[counter3,0],"
                "while["
                "less[counter3, len[l]], "
                "seq[if[eq[counter3, n], append[m3,s],get[l, counter3], append[m3,first[m]]], set[counter3, sum[counter3,1]]]"
                "]"
                "]"
                "]";


    char* get_check = "seq[get[r,1], first[m]]";
    char* test_drop = "seq[drop[r],h]";
    char * test_insert="seq[insert[r,2,l[1,2,3,4]], r]";
    char* check1 = "m";
    char* get_check2 = "get[r,1]";
    char* check2 = "first[m]";
    char* get_check3 = "get[r,2]";
//    char* check = "set[m,first[m]]";
    char* check3 = "first[m]";
    char* test2 = "h";

    solve(&If);



    solve(&While);


    solve(&test);

    solve(&get);

    solve(&get_check);
//        solve(&check1);
//    solve(&get_check2);
//    solve(&check2);
//    solve(&get_check3);
//    solve(&check3);

//    solve(&check);
//    solve(&check2);
//    solve(&drop);
//    solve(&test_drop);
    solve(&insert);
    solve(&test_insert);
//    solve(&test2);





    printContext();
    return 0;
}