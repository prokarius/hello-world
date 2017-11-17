#include<stdio.h>

int array[100005];

void setting(){
    int i;
    for (i=0; i<100003; ++i){array[i] = 0;}
}

int cmpfunc (const void * a, const void * b){
    return ( *(int*) a - *(int*)b);
}

int check (int R, int N, int K){
    // Returns 1 if it's possible. EMP missile style
    // Set the threshold radius to be array[0] + N
    // If we cross the treshold radius, start a new bomb.
    // If no more bombs, return 0. Else return 1.
    int i, curr = array[0]+R;
    for (i=0; i<N; ++i){
        if (array[i] > curr){
            curr = array[i] + R;
            if (--K <= 0){return 0;}
        }
    }
    return 1;
}

int cod(){
    setting();
    int B, K, x=-1;

    // Scan in the input
    scanf("%d %d", &B, &K);

    while (++x<K){
        int t;
        scanf("%d", &t);
        array[x] = t;
    }

    // Check if there are more access points than houses
    if (B >= K){
        printf ("0.0\n");
        return 0;
    }

    // Sort the input
    qsort(array, K, sizeof(int), cmpfunc);

    int high=1<<20, low=1<<20;
    // Binary search for the answer.
    while (low){
        if (check(high-low, K, B)){high -= low;}
        low /= 2;
    }

    // Print the results
    printf("%d.%d\n", high/2, 5*(high%2));
    return 0;
}

int main() {
    int N;
    scanf("%d",&N);
    while (N--){cod();}
    return 0;
}
