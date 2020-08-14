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
    // Note that the number of words is n, and the size of hash table is m
    int n, m;
    scanf("%d %d", &n, &m);

    // calloc my stuff
    Onion = malloc(sizeof(int) * m);
    ded = calloc(sizeof(int), m);

    onionInit(m);

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
    printf(flag?"successful hashing\n":"rehash necessary\n");

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
