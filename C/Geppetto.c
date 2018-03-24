#include<stdio.h>

int arr[401][401];
int head[21];
int chosen[21];
int n;

int recurse (int x){
    // Consider whether to take item x
    // Base: If x is the nth item, we win.
    if (x > n) return 1;

    // Else, see what happens when we do not take it
    int out = recurse(x+1);

    // Also consider when we take it, see if it causes any clash
    chosen[x] = 1;

    int i, flag = 1;
    for (i=0; i<head[x]; ++i){
        if (chosen[arr[x][i]]) flag = 0;
    }

    // If it doesn't, take the item and recurse.
    if (flag) out += recurse(x+1);

    // Don't forget to reset the item:
    chosen[x] = 0;
    return out;
}

int main(){
    int m, a, b;
    scanf("%d %d", &n, &m);
    while (m--){
        scanf ("%d %d", &a, &b);
        arr[a][head[a]++] = b;
        arr[b][head[b]++] = a;
    }
    printf ("%d\n", recurse(1));
    return 0;
}
