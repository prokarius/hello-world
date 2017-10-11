// Solution Discussed with Lingod

/*
3 Parts to this solution:
1) Find #ways for n people in a line so that no k women are together
2) Find #ways for n people so that x women in the front, y women in the rear
3) Remove rotationally symmetric shit

Part 1) f(n) = Number of ways in n people where no k women are together
For n<k, the number of ways is simply 2 ** n. -- (Eqn 1a)
We consider the left most man
He can be at most at the kth position starting from the left (0 based index)
Remove him and everyone to his left and we have a valid arrangement
Hence we can form a recurrance relation:
f(n) = f(n-1) + f(n-2) + ... + f(n-k) -- (Eqn 1b)
This takes O(nk) time.

Part 2) g(n) = Number of ways of n people are in a ring, no k women tgt
             = Number of unique ways for n people to sit together.
Now we gotta link this shit together
Since the middle is a valid arrangement, consider at the joining point
When x women in the front + y women in the rear < i, i<k = valid
Remove the women and you have a n-i valid combination, and we have
g(n)   = f(n) - 1  // Because of the all woman case -- (Eqn 2a)
g(k+1) = f(k+1)    // One guy + k women case        -- (Eqn 2b)
g(n)   = 1*f(n-2) + 2*f(n-3) + ... + (k-1)*f(n-k-2) -- (Eqn 2c)
This takes O(nk) time.

Part 3) h(n) = Number of ways of n people are in a ring, no k women tgt
So for i=0 to l. If l%i == 0 => We can decompose the h(i) strings into units.
i.e. ABABAB -> AB , ABAABAABAABA -> ABA
Remove these units. We will count them seperately.
So now we will unique strings of length n with no rotation symmetry
Since we counted each of these strings n times, we divide by n.
Oh no. Modulo Arithmetic. We cannot divide. Take mod inverse:
We have h[i] = g[i] - h[j], whenever i%j == 0 -- (Eqn 3a)
h[i] /= i => h[i] * inv(i) -- (Eqn 3b)
We only have to do this when n%i == 0, for reasons that will be clear later.

Part 4) Getting the answer
h(n) number of ways n people can sit in a circle rotationally distinctly
Now we just gotta sum it all up, for all factors of n. -- (Eqn 4a)
Oh and if n = k, add 1 for the all women case. -- (Eqn 4b)

*/

#include<stdio.h>
#define MOD 100000007
typedef long long ll;

ll inv[1002] = {0};

// Copied
ll minv(ll a){
    if (inv[a] != 0) return inv[a]; // Memoize
    ll m = MOD, t, q, x0 = 0, x1 = 1;
    while (a > 1)
    {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += MOD;
    return x1;
}

void code(){
    ll i, j, f[1002], g[1002], h[1002], n, k, output=0;
    scanf ("%lld %lld", &n, &k);
    if (k > n) k=n;

    // Eqn 1a
    f[0]=1;
    for(i=1; i<=k; ++i) f[i]=2*f[i-1] % MOD;

    // Eqn 1b
    for (i=k+1; i<=n; ++i) {
        f[i]=0;
        for (j=1; j<=k+1; ++j) f[i]=(f[i]+f[i-j]) % MOD;
    }

    // Eqn 2a, 2b, 2c
    for(i=0; i<=k; i++) g[i]=f[i]-1;
    g[k+1]=f[k+1];
    for (i=k+2; i<=n; ++i){
        g[i] = 0;
        for(j=2; j<=k+2; ++j) g[i]=(g[i]+(j-1)*f[i-j]);
    }

    // Eqn 3a
    for (i=1; i<=n; ++i) {
        h[i]=g[i];
        for (j=1; j<=(i/2); ++j) {
            if(i%j==0) h[i]=(h[i]-h[j]) % MOD;
        }
    }

    // Eqn 3b
    for (i=1; i<=n/2; ++i) h[i]=(h[i]*minv(i)) % MOD;
    h[n] = (h[n]*minv(n)) % MOD;


    // Eqn 4a
    for (j=1; j<=n/2; ++j) {
        if (n%j==0) output = (output+h[j]) % MOD;
    }
    output += h[n];

    // Eqn 4b
    if (n<=k) ++output;
    printf("%lld\n",(output+MOD) % MOD);
}

int main(){
    ll t;
    scanf ("%lld", &t);
    while (t--) code ();
    return 0;
}
