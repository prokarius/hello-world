#include<stdio.h>
#include<math.h>
#include<string.h>

#define MOD 1000000007
#define EPSILON 1e-12

typedef struct{
    long long invmod; // This is (10**amount)^-1
    long long mod; // This is 10**amount % MOD
    double amount; // This is log10(value)
} Mult;

Mult multlist[5000000];
int listhead=0;
long long primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
long long invprimes[] = {500000004,333333336,400000003,142857144,818181824,153846155,352941179,157894738,739130440,758620695,129032259,621621626,658536590,395348840,404255322,56603774,50847458,688524595,686567169,98591550,410958907,202531647,84337350,415730340,268041239};
int factors[25];
int list1[25], list2[25];
double bestAmount = -1;
double root = 0;
long long bestValue;
long long bestInverse;

// To push a new Mult into my ghetto array
void push(long long mod, double amount, long long inv){
    Mult new;
    new.invmod = inv;
    new.mod = mod;
    new.amount = amount;
    multlist[listhead++] = new;
}

// Comparator function for qsort
// We want to sort by the values of each mult.
int cmpfunc(const void * a, const void * b) {
    double value = ((Mult*)a)->amount - ((Mult*)b)->amount;
    return (0.0 < value) - (value < 0.0);
}

int binsearch (double target){
    // Returns the index of the best point given a certain target
    // Best is given by point that is lower than or almost equal to.
    // Low inclusive, High exclusive
    // Target is root - value to be determined
    int high = listhead;
    int low = 0;
    while (high - low != 1){
        int mid = (high + low)/2;
        if (multlist[mid].amount <= target) low = mid;
        else high = mid;
    }
    return low;
}

void recursivePush (int curr, long long value, double amount, long long inv){
    // We will recursively push stuff into our multlist
    // Base case when curr is at the end of the list, we push
    if (curr == 25){
        push(value, amount, inv);
        return;
    }

    // For each possible power of the prime, we will push it.
    int i;
    long long prime = primes[curr], invprime = invprimes[curr];
    double logten = log10(prime);
    long long newValue = value;
    long long newinv = inv;
    double newAmount = amount;
    recursivePush(curr+1, newValue, newAmount, newinv);
    for (i=0; i<list1[curr]; ++i){
        newValue = (newValue * prime) % MOD;
        newinv = (newinv * invprime) % MOD;
        newAmount += logten;
        recursivePush(curr+1, newValue, newAmount, newinv);
    }
}

void recursiveSolve (int curr, long long value, double amount, long long inv){
    // So we use recursion to check which is the best.
    // Base case: when curr is at the end of the list, we check
    if (curr == 25){
        if (root - amount < 0){
            return;
        }
        // Remember that root - amount is the target
        int ansindex = binsearch((root - amount) + EPSILON);
        double totalAmount = (multlist[ansindex].amount + amount);
        long long bestinv = (multlist[ansindex].invmod * inv) % MOD;
        long long bestV = (multlist[ansindex].mod * value) % MOD;
        if (totalAmount > bestAmount){
            // This means we have a new best value
            bestValue = bestV;
            bestAmount = totalAmount;
            bestInverse = bestinv;
        }
        else if ((totalAmount == bestAmount) && (bestValue > bestV)){
            bestValue = bestV;
            bestInverse = bestinv;
        }
        return;
    }

    // For each possible power of the prime, we will push it.
    int i, prime = primes[curr], invprime = invprimes[curr];
    double logten = log10(prime);
    long long newValue = value;
    long long newinv = inv;
    double newAmount = amount;
    recursiveSolve(curr+1, newValue, newAmount, newinv);
    for (i=0; i<list2[curr]; ++i){
        newValue = (newValue * prime) % MOD;
        newinv = (newinv * invprime) % MOD;
        newAmount += logten;
        recursiveSolve(curr+1, newValue, newAmount, newinv);
    }
}

int main(){
    char ph1, ph2;
    int curr, total = 0, factptr = 0;
    long long out = 0;
    long long totalProduct = 1;
    int i, j, k=0;
    char input[705];
    // Scan in input
    scanf ("%s", &input);
    int len = strlen(input);

    for (k=0; k<len/2; ++k){
        ph1 = input[2*k];
        ph2 = input[2*k+1];
        curr = (ph1-'0')*10 + (ph2-'0');
        for (i=0; i<25; ++i){
            if (primes[i] == curr){
                factors[i]++;
                break;
            }
        }
        totalProduct = (totalProduct * curr) % MOD;
        root += log10(curr);
        ++total;
    }

    // Square root the root. This will be our target
    root /= 2;

    // Calculate how equal the number of divisors can be
    // We will try to split the factors so that we get to this number
    long long numdivs = 1;
    for (i=0; i<25; ++i) numdivs *= (factors[i] + 1);
    numdivs = (long long) sqrt(numdivs);

    // Partition into two halves so that the number of factors is roughly equal
    long long numfactors = 1;
    i = 0;
    while (numfactors <= numdivs){
        numfactors *= 1 + factors[i];
        list1[i] = factors[i];
        ++i;
    }

    --i;

    // When we are here, means we have added too many factors
    // Add just enough to make it slightly less than half.
    // So list1 will contain all the factors such that the number of multiples
    // are as close to half as can be
    numfactors /= factors[i] + 1;
    list1[i] = (numdivs / numfactors);

    // Then to make list2, we just copy over all the other factors
    list2[i] = factors[i] - list1[i];
    while (++i < 25) list2[i] = factors[i];

    // Generate a list that is all possible multiples of the first group
    // Is it time for recursion? :D
    recursivePush(0, 1, 0, 1);

    // qsort multlist by amount.
    qsort(multlist, listhead, sizeof(Mult), cmpfunc);

    // It's time for MOAR RECURSION!
    // for each possible factor from group 2
    // Binary search to find the factor in multlist that is closest to target
    recursiveSolve(0, 1, 0, 1);

    // Now that we have found one of the factors, we need to find the other one
    // Take the total product and multiply by the inverse.
    long long otherValue = (totalProduct * bestInverse)%MOD;

    // print out the final answer
    printf ("%lld\n", (bestValue + otherValue)%MOD);
    return 0;
}
