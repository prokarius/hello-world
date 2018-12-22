#include<stdio.h>

typedef struct{
    int dist;
    short x;
    short y;
} Edge;

// This cmpfunc is only for comparisons though
// Not for qsort.
int cmpfunc(Edge a, Edge b){
    return (a.dist - b.dist);
}

// Yes, I finally decided to make my own ghettoHeap.
// I think this completes the basic data structures list...
Edge ghettoHeap[1000000];

void push(Edge e){
}

int pop(Edge e){
}

int main(){

    return 0;
}
