#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b){
   float x = *(float*) a;
    float y = *(float*) b;

    if(x > y) return -1;
    else return 1;
}

int main(){
    int passnum = 0, i;
    float prob = 0.0, curprob = 0.0;
    scanf ("%d", &passnum);
    float listprob[passnum];
    for (i=0; i < passnum; i++){
        scanf ("%*s %f", &curprob);
        listprob[i] = curprob;
    }
    qsort(listprob, passnum, sizeof(float), cmpfunc);

    for (i=0; i<passnum; i++){
        prob += (i+1)*listprob[i];
    }
    printf ("%f", prob);
    return (0);
}
