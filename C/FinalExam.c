#include<stdio.h>

#define MAX(x, y) (x>y)?(x):(y)

int memo[1<<13][1<<13];

// Maybe I need to memoize to make it faster...
int gcd(int a, int b){
    if (memo[a][b]) return memo[a][b];
    if (!b) return a;
    memo[a][b] = gcd(b, a%b);
    return memo[a][b];
}

int countA[1<<25];
int countB[1<<25];
int countC[1<<25];

// Ugh, a question in unnecessary optimization :D
int squares[1<<13];

int main(){
    // Scan in input
    int numA, numB, numC;
    scanf("%d %d %d", &numA, &numB, &numC);

    int x;
    for (int i = 0; i < numA; ++i){
        scanf("%d", &x);
        ++countA[x];
    }
    for (int i = 0; i < numB; ++i){
        scanf("%d", &x);
        ++countB[x];
    }

    int maxC = -1;
    for (int i = 0; i < numC; ++i){
        scanf("%d", &x);
        maxC = MAX(maxC, x);
        ++countC[x];
    }

    for (int i = 1; i < 6000; ++i){
        squares[i] = i*i;
    }

    // Use wikipedia's method of generating pythagorean triples
    long long out = 0;

    int m = 2;
    while(m * m < maxC){
        // n and m must be of different parities
        // m must be bigger than n
        // m and n are coprime
        for (int n = (m&1) + 1; n < m; n += 2){
            if (n*n + m*m > maxC) break;
            if (gcd(n, m) != 1) continue;

            int a = 2*m*n;
            int b = squares[m] - squares[n];
            int c = squares[m] + squares[n];

            int currA = a;
            int currB = b;
            int currC = c;

            // Then keep scaling
            while (currC <= maxC){
                // Maybe multiplying is expensive...

                if (countA[currA] && countB[currB] && countC[currC]){
                    out += 1LL * countA[currA] * countB[currB] * countC[currC];
                }
                if (countA[currB] && countB[currA] && countC[currC]){
                    out += 1LL * countA[currB] * countB[currA] * countC[currC];
                }

                currA += a;
                currB += b;
                currC += c;
            }
        }
        ++m;
    }

    printf("%lld\n", out);
    return 0;
}

