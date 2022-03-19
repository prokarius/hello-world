#include<stdio.h>

int ABS(int x){ return x>0?x:-x; }

int main(){
    // Scan in input
    int m, l, M, L, tm, tl;
    scanf("%d %d %d %d %d %d", &m, &l, &M, &L, &tm, &tl);
    int ok = 0;

    // Get one to them to their goal, then the other
    if ((ABS(l) + ABS(L-l) <= tl) && (ABS(l) + ABS(L-l) + ABS(m-L) + ABS(M-m) <= tm)) ok = 1;
    if ((ABS(m) + ABS(M-m) <= tm) && (ABS(m) + ABS(M-m) + ABS(l-M) + ABS(L-l) <= tl)) ok = 1;

    // Swap l and m's positions, then try again
    if((ABS(l) + ABS(m-l) + ABS(M-m) <= tm) && (ABS(l) + ABS(m-l) + ABS(M-m) + ABS(m-M) + ABS(L-m)<= tl)) ok = 1; 
    if((ABS(m) + ABS(l-m) + ABS(L-l) <= tl) && (ABS(m) + ABS(l-m) + ABS(L-l) + ABS(l-L) + ABS(M-l)<= tm)) ok = 1; 

    if (!ok) printf("im");
    printf("possible\n");

    return 0;
}

