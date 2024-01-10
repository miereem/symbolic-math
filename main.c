#include "solver.h"
#include "stdlib.h"
#include "transformer.h"
#include "graph.h"

int main() {

//     char *input = "seq[set[d[p_],0],set[pow[n_,x_],mul[n,n]],setDelayed[d[pow[x_,n_]],mul[n,pow[x,sum[n,-1]]]],pow[5,2],d[1]]";
//     char *input1 = "d[pow[5,2]]";
//    char *fib = "seq[set[f[0],0],set[f[1],1],set[f[2],1],setDelayed[f[n_],sum[f[sum[n,-1]],f[sum[n,-2]]]],f[20]]";

    char *If = "seq[setDelayed[if[true,t_,e_],t],setDelayed[if[false,t_,e_],e],]";
    char *While = "setDelayed[f[x_],if[less[x,3],1,sum[f[sum[x,-1]],f[sum[x,-2]]]]]";

    char *input = "f[4]";
    char *der = "seq[set[d[p_],0],set[d[sin[p_]],cos[p]]]";
    char *der0 = "seq[set[d[p_],0],set[d[cos[p_]],sum[sin[p],-1]]]";
    char *der1 = "d[sin[p]]";

    initContext();
//    solve(&fib);
    solve(&If);
    solve(&While);
    solve(&input);
    solve(&der);
    solve(&der1);
    printContext();

        PointArray pointArray;
        pointArray.count = 3;
        pointArray.points= malloc(sizeof(Point)*3);
        pointArray.points[0].x=1;
        pointArray.points[0].y=16;
        pointArray.points[1].x=2;
        pointArray.points[1].y=3;
        pointArray.points[2].x=0;
        pointArray.points[2].y=2;

    PointArray pointArray2;
    pointArray2.count = 3;
    pointArray2.points= malloc(sizeof(Point)*3);
    pointArray2.points[0].x=1;
    pointArray2.points[0].y=6;
    pointArray2.points[1].x=2;
    pointArray2.points[1].y=37;
    pointArray2.points[2].x=6;
    pointArray2.points[2].y=12;
        struct Plots plots;
    plots.plots = malloc(sizeof(PointArray)*2);
    plots.plots[0]=pointArray;
    plots.plots[1]=pointArray2;
        plots.count=2;
        plot(plots, 500, 400);

    return 0;
}