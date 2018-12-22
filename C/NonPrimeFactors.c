#include<stdio.h>

#define MAX 2000002

int factors[MAX];
int primefactorsdp[MAX];
int totalfactorsdp[MAX];
int answerdp[MAX];

// Count the total number of factors of a given number
int totalFactors(int n){
    // Have we cached the result before?
    if (totalfactorsdp[n] != 0) return totalfactorsdp[n];

    // This means it is a prime, so 2 factors!
    if (factors[n] == 0) return 2;

    // OK if not, lets count the number of factors
    int prime = factors[n];
    int newn = n;
    while (newn % prime == 0){
        newn = newn / prime;
    }

    // Get the correct result
    // Also, save the correct number of factors
    int numPrime = 1;
    int out = totalFactors(newn);

    // Cache the results in the dp table
    while (newn < n){
        newn *= prime;
        numPrime++;
        totalfactorsdp[newn] = out * numPrime;
    }

    return out * numPrime;
}

// Counts the number of prime factors given a given number
int primeFactors(int n){
    // Have we cached the result before?
    if (primefactorsdp[n] != -1) return primefactorsdp[n];

    // This means it is a prime
    if (factors[n] == 0) return 1;

    // OK if not, we need to count the number of prime factors
    // Get rid of all prime factors associated with this number
    int prime = factors[n];
    int newn = n;
    while (newn % prime == 0){
        newn /= prime;
    }

    // Add 1 to the number of primeFactors
    int out = 1 + primeFactors(newn);

    // But before returning, we will cache the results
    while (newn < n){
        newn *= prime;
        primefactorsdp[newn] = out;
    }
    return out;
}


int main(){
    // For each number, generate the list of factors.
    // factors[i] stores the smallest prime factor of i.
    // Shitty prime sieve going on here.
    for (int i = 2; 2*i < MAX; ++i){
        if (factors[i] != 0) continue;

        // For each composite number that has i, we say the factor is i
        for (int j = 2*i; j < MAX; j += i){
            factors[j] = i;
        }
    }

    // Reset the dparrays
    for (int i = 0; i < MAX; ++i){
        primefactorsdp[i] = -1;
    }

    // Set up the number of factors dp
    primefactorsdp[1] = 0;
    totalfactorsdp[1] = 1;

    int q;
    scanf("%d", &q);

    // For each query
    for (int i = 0; i < q; ++i){
        int num;
        scanf("%d", &num);

        // Check if we have cached the results
        if (answerdp[num] != 0){
            printf("%d\n", answerdp[num]);
            continue;
        }

        // Else, calculate it.
        int out = totalFactors(num) - primeFactors(num);
        answerdp[num] = out;
        printf("%d\n", out);
    }

    return 0;
}
