// Mon dieu! This is the same question as Cuckoo Hashing!

#include<stdio.h>
#include<stdlib.h>

int* Onion;
int* ded;
int flag;

void onionInit(int n){
    for (int i = 0; i < n; ++i){
        Onion[i] = i;
    }
}

int find(int x){
    if (Onion[x] != x){
        Onion[x] = find(Onion[x]);
    }
    return Onion[x];
}

// For why this works, look at Ladice.c
void onion(int x, int y){
    int parentx = find(x);
    int parenty = find(y);

    if (ded[parentx] && ded[parenty]){
        flag = 0;
        return;
    }

    if (parentx == parenty){
        ded[parentx] = 1;
        return;
    }

    Onion[parentx] = parenty;

    if (ded[parentx] || ded[parenty]){
        ded[parentx] = 1;
        ded[parenty] = 1;
    }
}

void solve(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // calloc my stuff
    // Ugh it's one indexed
    Onion = malloc(sizeof(int) * 2*n+1);
    ded = calloc(sizeof(int), 2*n+1);

    onionInit(2*n+1);

    // If the hash is still possible, flag will be 1;
    flag = 1;

    // Do online processing
    for (int i = 0; i < n; ++i){
        int a, b;
        scanf("%d %d", &a, &b);

        // Don't bother processing if we have died
        if (flag == 0) continue;

        // Onion the onion
        onion(a, b);
    }

    // If we are good, flag will be 1
    printf(flag?"":"im");
    printf("possible\n");

    // Don't forget to free dobby...
    free(Onion);
    free(ded);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}
