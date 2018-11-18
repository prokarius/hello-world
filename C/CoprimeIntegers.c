#include<stdio.h>
#include<stdlib.h>

#define MIN(x, y) (x < y)?(x):(y)

int* hasSquareNumberFactor;
int* numPrimeFactors;

long long coprimePairs(long long x, long long y){
    // Essentially, we assume all possible x and y pairs are coprime to each other.
    // Then we will subtract the pairs that are actually not coprime to each other.

    // First set it up so that we say all possible pairs are coprime.
    long long allPairs = x * y;

    // Now, for each possible divisor, we want to find out how many pairs that we
    // have considered in allPairs are have this divisor as a factor.
    for (int i = 2; i <= (MIN(x, y)); ++i){
        // Oh but even before that, should we take into account numbers that have
        // divisors with >= 2 power?
        // We should not! Because we would be double counting!
        if (hasSquareNumberFactor[i]){
            continue;
        }

        // This isn't too difficult, as we just need to divide x and y by the divisor
        // and multiply them together to get the actual number.
        // Why this works? See figure 2 below.
        long long numPairsIDivisor = (x/i) * (y/i);

        // Now the PIE happens here. If the divisor we are considering (i) has an
        // ODD number of prime factors, then we know we need to remove it.
        // But if it has an EVEN number of prime factors, then we have to add it
        // back! This is really just PIE!

        // This is why we needed to count the number of distinct prime factors each
        // number has!
        if (numPrimeFactors[i] % 2 == 1){
            allPairs -= numPairsIDivisor;
        }
        else {
            allPairs += numPairsIDivisor;
        }
    }
    return allPairs;
}

/* FIGURE 1 -- Why we can just do (a/i)*(b/i)

   a
   ^
   |
5a +  x  x  x  x  x
   |
4a +  x  o  x  o  x
   |
3a +  x  x  x  x  x
   |
2a +  x  o  x  o  x
   |
 a +  x  x  x  x  x
   |
   +--+--+--+--+--+---> b
      a 2a 3a 4a 5a

xs represent pairs where the values have a as a divisor.
os represent pairs where a*a (In this case, a = 2) is a divisor.

Notice that the xs and os are neatly spaced out in a grid.
Every a units, in either direction, we will have either an x or an o.
In this case, we can say that the number of points on this grid is simply the number of
xs (and os) in each row, multiplied by the number of rows.

The number of columns = (b/i)
The number of rows = (a/i)

Therefore the total number = (a/i) * (b/i)

Now the question becomes, do we need to care about the os?
The answer is: No!
Because when we consider some divisor i, we would have automatically added in every
o into the count of the number of pairs where both elements share i as a divisor.

I.e. Given (p, q), if a*2 | p and a*2 | q, then a | p and a | q.
Therefore the pair (p, q) would have already been subtracted off!

Hence, we do not care about numbers which has a square number as a factor.
*/

int main(){
    // Scan in input
    long long a, b, c, d;
    scanf("%lld %lld %lld %lld", &a, &b, &c, &d);

    // We need to initialise some tables. These will help us as per the explanations
    // in the above function.

    // Why we consider the min of b and d to be the maxValue?
    // Because suppose we consider some divisor x where b < x < d.
    // The number of pairs of (p, q) where x | p and x | q and p < b, q < d
    // will be 0. Simply because if x | p, then p must be at least x.
    // But this directly contradicts p < b. Hence.
    long long maxValue = MIN(b, d);

    hasSquareNumberFactor = (int*) calloc(maxValue + 1, sizeof (int));
    numPrimeFactors = (int*) calloc(maxValue + 1, sizeof (int));

    // We are going to loop through all numbers from i = 2 up to maxValue
    for (long long i = 2; i <= maxValue; ++i){
        // Now, if i isn't even a prime number (numPrimeFactors[i] > 1) then
        // we can simply ignore it. We are counting prime numbers anyways...
        if (numPrimeFactors[i] > 0){
            continue;
        }

        // If not, we need to add 1 to all its multiples to mark that said multiples
        // has i as a prime factor
        for (int j = i; j <= maxValue; j += i){
            ++numPrimeFactors[j];
        }

        // Now we just need to mark all the numbers which has i*i as a factor...
        long long isquared = i*i;
        long long j = isquared;
        while (j <= maxValue){
            hasSquareNumberFactor[j]++;
            j += isquared;
        }
    }
    // We will use some PIE in this solution.
    // Suppose we have a function coprimePairs that given x and y, returns me the
    // number of coprime pairs (a, b) such that 1 <= a <= x, and 1 <= b <= y.
    // Then we can just do PIE on this! (See Figure 1 below)
    long long out = (coprimePairs(b, d) + coprimePairs(a-1, c-1)) -
        (coprimePairs(b, c-1) + coprimePairs(a-1, d));
    printf("%lld\n", out);
}

/* FIGURE 2:

  ^
b +
  |////////|oooooooo
  |////////|oooooooo
  |////////|oooooooo
a +--------+---------
  |xxxxxxxx|\\\\\\\\
  |xxxxxxxx|\\\\\\\\
  |xxxxxxxx|\\\\\\\\
  +--------+--------+->
           c        d

If we did f(b, d), we will count the \, / and x regions.
So we can subtract f(b, c) and f(a, d) to get rid of the \ and / regions
But by doing so, we get rid of the x region more than once.
So we add f(a, c) back!

*/
