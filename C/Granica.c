#include<stdio.h>
#include<stdlib.h>

#define ABS(x) ((x)>0)?(x):(-(x))

int numPrimes = 0;
int primesList [1<<16];
int primes[1<<16];

// Prime numbers generator
// Generates all prime numbers to n
// Sets the global variables as above
void genPrimes(int n) {
    primes[0] = primes[1] = 1;
    for (int i = 0; i*i < n; ++i){
        if (primes[i] != 0){
            continue;
        }
        primesList[numPrimes] = i;
        numPrimes++;
        for (long long j = i; j*j < n; j += i){
            primes[j] = 1;
        }
    }
}

int GCD(int a, int b){
    while (b){
        int c = b;
        b = a%c;
        a = c;
    }
    return a;
}

// For prime factorization
int factors[32];
int numFactors[32];
int k = 0;

int divisors[1<<16];
int numDivisors = 1;

void divisorsRecurse(int currIndex){
    if (currIndex == k) return;
    int currNumDivisors = numDivisors;

    int currPrime = factors[currIndex];
    int currNumFactors = numFactors[currIndex];

    for (int i = 0; i < currNumDivisors; ++i){
        int currNum = divisors[i];
        for (int j = 0; j < currNumFactors; j++){
            currNum *= currPrime;
            divisors[numDivisors] = currNum;
            numDivisors++;
        }
    }
    divisorsRecurse(currIndex + 1);
}

int input[128];

int main(){
    // Generate primes before anything else
    genPrimes(1000000001);

    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &input[i]);
    }
    
    // Find the gcd of the differences
    int gcd = ABS(input[1] - input[0]);
    for (int i = 2; i < n; ++i){
        gcd = GCD(gcd, ABS(input[i] - input[i-1]));
    }

    // Prime factorize the gcd.
    for (int i = 0; i < numPrimes; ++i){
        int currPrime = primesList[i];
        if (gcd % currPrime == 0){
            factors[k] = currPrime;
            numFactors[k] = 0;

            while (gcd % currPrime == 0){
                numFactors[k]++;
                gcd /= currPrime;
            }
            k++;
        }
    }

    if (gcd != 1){
        factors[k] = gcd;
        numFactors[k] = 1;
        k++;
    }

    // Make all possible divisors from the factors
    divisors[0] = 1;
    divisorsRecurse(0);

    // Now we check all the possible divisors, excluding 1.
    for (int i = 1; i < numDivisors; ++i){
        int goal = input[0] % divisors[i];
        for (int j = 1; j < n; ++j){
            if (input[j] % divisors[i] != goal){
                goal = -1;
                break;
            }
        }

        if (goal != -1){
            printf("%d ", divisors[i]);
        }
    }

    return 0;
}
