#include<stdio.h>

int Onion[1024];

int find(int x){
    if (Onion[x] != x){
        Onion[x] = find(Onion[x]);
    }
    return Onion[x];
}

// Returns 1 if unionable
int onion(int x, int y){
    int parentX = find(x);
    int parentY = find(y);

    if (parentX == parentY) return 0;
    Onion[parentX] = parentY;
    return 1;
}


void solve(){
    // Scan in input
    int m, r;
    scanf("%d %d", &m, &r);

    // Create the onion
    for (int i = 0; i < m; ++i) Onion[i] = i;

    for (int i = 0; i < r; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        m -= onion(x, y);
    }

    printf("%d\n", m-1);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}
