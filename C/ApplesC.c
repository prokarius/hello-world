#include <stdio.h>
#define MOD 1000000007
typedef long long ll;

ll factorial[400004], inverse[200002], p2[200005], na=1;

// Setting up the precomputation for x!, x!^-1 (mod p) and 2^x.
void setting (){
    ll i, na = 1, a, output, ph;
    factorial[0] = 1;
    inverse[0] = 1;
    for (i=1; i<400004; ++i){
        na = (na*i)% MOD;
        factorial[i] = na;
    }

    for (i=1; i<200002; ++i){
        a = factorial[i];
        output = 1;
        ph = MOD-2;
        while (ph){
            if (ph % 2 == 1) output = (output*a) % MOD;
            a = (a*a) % MOD;
            ph = ph >> 1;
        }
        inverse [i] = output;
    }

    p2[0] = ph = 1;
    for (i=1; i<200005; ++i){
        ph = (ph*2) % MOD;
        p2[i] = ph;
    }
}

ll chose (ll N, ll r){
    if (N>=r){
        ll g = (factorial[N]*inverse[N-r]) % MOD;
        return (g * inverse[r]) % MOD;
    }
    return 0;
}


ll ways (ll A, ll x, ll y, ll z){
    // Calculates the number of perms of A = x+y+z objects
    if (x<0 || y<0 || z<0) return 0;
    ll output = (factorial[A] * inverse[x]) % MOD;
    output = (output * inverse[y]) % MOD;
    return (output * inverse[z]) % MOD;
}

ll buck (ll A, ll C, ll M){
    // Calculates the number of ways of possible solutions
    if (A==0 || A > C+M) return 0;
    ll output = 0, i=0, j, k, new;
    while (i <= 1+(A+M-C)/2){
        j = C-M+i;
        k = A-(i+j);
        if (M-i-k >= 0 && k>=0){
            new = (ways (A, i, j, k) * chose (M-i-k+A-1,A-1)) % MOD;
            new = (new * p2[k]) % MOD;
            output = (output + new) % MOD;
        }
        ++i;
    }
    return output;
}

int main(){
    // Initialise and scan
    setting();
    ll A, B, C, i, ph, output;
    scanf ("%lld %lld %lld", &A, &B, &C);
    // Sort
    if (A < B){
        ph = B;
        B = A;
        A = ph;
    }
    if (B < C){
        ph = C;
        C = B;
        B = ph;
    }
    if (A < B){
        ph = B;
        B = A;
        A = ph;
    }
    // Note that between each A, there must exist at least 1 B or C.
    // WLOG, fix A as the greatest of the 3. Then soln = sum of 3 cases:
    // Case 1: When the front AND back are As
    // Case 2: When the front XOR back are As (2 such cases)
    // Case 3: When the front AND back are not As.
    output = (buck(A+1, B, C) + buck(A-1, B, C) + 2*buck(A, B, C)) % MOD;
    printf ("%lld\n", output);
    return 0;
}
