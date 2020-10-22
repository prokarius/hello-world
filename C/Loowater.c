#include<stdio.h>
#include<stdlib.h>

int heads[20005];
int knights[20005];

int cmpfunc(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

void solve(int n, int m){
    // Scan in input
    for (int i = 0; i < n; ++i){
        scanf("%d", &heads[i]);
    }

    for (int i = 0; i < m; ++i){
        scanf("%d", &knights[i]);
    }

    // Sort the knights and dragons
    qsort(heads, n, sizeof(int), cmpfunc);
    qsort(knights, m, sizeof(int), cmpfunc);

    // Greedy
    long long out = 0;
    int curr = 0;
    for (int i = 0; i < m; ++i){
        if (knights[i] >= heads[curr]){
            out += knights[i];
            curr++;
            if (curr == n) break;
        }
    }

    if (curr != n){
        printf("Loowater is doomed!\n");
    }
    else {
        printf("%lld\n", out);
    }
}

int main(){
    int n, m;

    scanf("%d %d", &n, &m);

    while (n != 0 && m != 0){
        solve(n, m);
        scanf("%d %d", &n, &m);
    }

    return 0;
}

