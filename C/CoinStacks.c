#include<stdio.h>
#include<stdlib.h>

// We'll just do the unoptimized solution...
typedef struct {
    int coins;
    int stack;
} Stack;

Stack stacks[64];
int out[512][2];

int cmpfunc(const void* a, const void* b){
    return (*(Stack*)b).coins - (*(Stack*)a).coins;
}


int main(){
    // Scan in input
    int n;
    int sum = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int x;
        scanf("%d", &x);
        sum += x;

        Stack new;
        new.coins = x;
        new.stack = i+1;
        stacks[i] = new;
    }

    // Just greedily take 2 from the largest piles each time
    for (int i = 0; i < sum/2; ++i){
        qsort(stacks, n, sizeof(Stack), cmpfunc);

        if (stacks[1].coins == 0) break;

        out[i][0] = stacks[0].stack;
        out[i][1] = stacks[1].stack;
        stacks[0].coins--;
        stacks[1].coins--;
    }

    // If we have anything leftover, it's not possible
    qsort(stacks, n, sizeof(Stack), cmpfunc);
    if (stacks[0].coins){
        printf("no\n");
        return 0;
    }

    printf("yes\n");
    for (int i = 0; i < sum/2; ++i){
        printf("%d %d\n", out[i][0], out[i][1]);
    }
    return 0;
}

