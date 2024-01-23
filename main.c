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
    char * test = "set[r,l[l[1,2,3],l[2,3,4],l[3,4,5]]]";

    char* main = "while[less[const,3],seq[set[const,sum[const,1]],set[r,rest[r]]]]";
    char* drop = "setDelayed["
                "drop[list_],"
                "seq["
                "set[h,l[]],"
                "set[counter2,1],"
                "while["
                "less[counter2, len[list]], "
                "seq[get[list, counter2],append[h, rest[m]], set[counter2, sum[counter2,1]]]"
                "]"
                "]"
                "]";

    char* get = "setDelayed["
                "get[list_,index_],"
                "seq["
                "set[m,list],"
                "set[counter,0],"
                "while["
                        "less[counter,index],"
                        "seq[ set[counter,sum[counter,1]] ,set[m,rest[m]] ] "
                "]"
                "]"
                "]";

    char* get_check = "seq[get[r,2],set[m2,first[m]]]";
    char* check = "set[m,first[m]]";
    char* check2 = "m2";
    char* test_drop = "drop[r]";
    char* test2 = "h";

    solve(&If);



    solve(&While);


    solve(&test);

    solve(&get);

    solve(&get_check);

//    solve(&check);
    solve(&check2);
    solve(&drop);
//    solve(&test_drop);
//    solve(&test2);





    printContext();
    return 0;
}