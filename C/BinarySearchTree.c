#include<stdio.h>
// #define MAX(x,y) ((x)>(y)?(x):(y))

// Array to store what depths we want to compare.
// Array to store the depths of the nodes.
int depth[300005], compare[300005][2];

int MAX(int a, int b){
    return a > b ? a : b;
}

int main(){
    int i, k, N, input [300005], dll[300005][2];
    long long output = 0;
    scanf("%d", &N);

    // First generate a doubly linked list of all the elements from 1 to N
    // We will do this by making an array call it DLL
    // dll[index][0] stores prev value
    // dll[index][1] stores succ value
    for (i=1; i<=N; ++i){
        dll[i][1] = i+1;
        dll[i][0] = i-1;
    }

    dll[N][1] = 0;

    // Scan in the input
    for (i=0; i<N; ++i){
        scanf ("%d", &k);
        input[i] = k;
    }

    // From the back of the input, store the values of what we need to compare
    // This will be stored in the global compare array
    // Then pop the node from the doubly linked list
    // This works because each value from 1 to N only gets input once
    // This hack won't work if the values don't go from 1 to N
    k = N;
    while (--k){
        i = input[k];
        // Do we need to care about the edge cases? No!
        // Because we set it to 0. depth[0] is 0, and max of anything and 0 is
        // that thing. So the depth would therefore be the depth of the other thing.
        compare[k][0] = dll[i][0];
        compare[k][1] = dll[i][1];

        // We set the next of the smaller element to be the next of the popped node
        // We set the prev of the larger element to be the prev of the popped node
        dll[dll[i][0]][1] = dll[i][1];
        dll[dll[i][1]][0] = dll[i][0];
    }

    // Now, simulate!
    // It can be shown that the depth of the inserted node will be the maximum
    // of the depth of the next greater element, and the next smaller element + 1
    // So we can just dp this!
    i = -1;
    while (++i < N){
        depth[input[i]] = MAX(depth[compare[i][0]], depth[compare[i][1]]) + 1;
        output += depth[input[i]]-1;
        printf ("%lld\n", output);
    }
    return 0;
}
