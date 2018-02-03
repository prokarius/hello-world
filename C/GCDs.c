#include<stdio.h>

int gcds[101][2], out[101];

int gcd(int x, int y){
    while (y){
        int z = y;
        y = x%y;
        x = z;
    }
    return x;
}

int main(){
    // Scan in the input
    int T, n, i, newgcd, ans = 0;
    scanf("%d", &T);

    // For each number scanned, we compute the gcd of it with all older gcds
    // Older GCDs are stored in an array[100]
    // Simply loop through the array per run.
    // See MagicalGCD.py in Python folder to see the main logic behind the algo.
    while (T--){
        scanf("%d", &n);
        for (i = 1; i<101; ++i){
            if (gcds[i][T%2]){
                newgcd = gcd(i, n);
                gcds[newgcd][(1+T)%2] = 1;
                if (1-out[newgcd]){
                    ++ans;
                    ++out[newgcd];
                }
                gcds[i][T%2] = 0;
            }
        }
        if (1-gcds[n][1+T%2]) ++gcds[n][(1+T)%2];
        if (1-out[n]){
            ++out[n];
            ++ans;
        }
    }
    printf ("%d\n", ans);
    return 0;
}
