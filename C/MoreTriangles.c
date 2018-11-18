#include<stdio.h>

long long array[500005];
// array[n] = number of i such that i^2 == n
// Well, we will be using this a lot, n will change, depending where we are
// Hence you will see a lot of cleaning

long long thething (long long p, long long expo){
    // Number of solutions for a^2 + b^2 = c^2 (mod p^expo)
    // But if exponent = 0, then there is only trivial solution
    if (expo == 0) return 1;
    long long n=1, i, sq, output = 0;
    // Wait what is p^e again?
    for (i = 0; i< expo; ++i) n *= p;
    // Clean and populate our array with _Quadratic Residues_ of all i < n
    // See: http://www.math.brown.edu/~jhs/MA0042/FRINTNewCh2324.pdf
    for (i=0; i<n; ++i) array[i] = 0;
    for (i=0; i<n; ++i) ++array[i*i % n]; 

    // 3 cases: CASE 1) When a != 0 (mod p) AND b != 0 (mod p)
    //        : CASE 2) When a != 0 (mod p) XOR b != 0 (mod p)
    //        : CASE 3) When 2 == 0 (mod p) AND b == 0 (mod p)
    // We need to deal with them seperately

    // CASE 1) Get the pairwise multiplication of all quadratic residues
    // This is kinda like FFT. We can do this in O(n) time cuz of symmetry.
    // So how to cheat? Well, assume b^2 == 1^* (mod p)
    // Now we find the number of ways a^2 + 1 == c^2 (mod p)
    for (i=0; i<n; ++i) output += array[i]*array[(i+1)%n];

    // CASE 2) When p divides either one of a^2 or b^2
    // WLOG, assume p divides a^2. Again, assume b^2 == 1^* (mod p)
    // Then divide a^2 by p, and loop. (Or iterate for i=0 to n, i+=p)
    // Same thing, we find number of ways a^2 + 1 == c^2 (mod p) 
    for (i=0; i<n; i+=p){
        sq = (i*i+1)%n;
        output += array[sq];
    }
    // For CASE 1 & 2, we can find a modulo inverse q such that q*(x-y) = 1
    // From here we can multiply q by any of 1 - p-1 to get all p-1 values
    // i.e. We have assumed a^2 == 1 (mod p), we need to generalise this
    // And since there are (p-1) other ways this can happen:
    // i.e. There are (p-1) equivalent classes
    // ^*This is why we could have replaced 1 in line 29 with any other int
    output *= (p-1);

    // If n = p^x, then every (n/p), this pattern will repeat
    output *= (n/p);

    // CASE 3) has 2 cases:
    // CASE 3a) What if expo > 1?
    // When i%p == 0, there will be p distinct i such that i^2 == 0 (mod p)
    // => All n for i = 0 (mod p) && i = n (mod p) has the same solution
    // So we divide each of the a,b,c by p, and find the number of solutions
    // Since there will be p repetitions, for a,b,c, we multiply by p^3
    if (expo > 1) output += thething (p, expo-2)*p*p*p;
    // CASE 3b) Else, we just have to account for a=b=c=0, so +1.
    else ++output;
    return output;
}

long long diag (long long n){
    // Number of solutions when a^2 = b^2. i.e. along the diagonal
    long long i, output=0;
    for (i=1; i<n; ++i){
        // a=i, b=i, c=2*i*i%n
        output += array[(2*i*i)%n];
    }
    return output;
}

long long zero (long long n){
    // Number of solutions when a, b or c is 0
    long long i, output=0;
    for (i=0; i<n; ++i){
        // a=i, b=0, c=i
        // x2 because a and b can swap places
        output += 2 * array[i] * array[i];
        // a=i, b=n-i, c=0
        // no need x2 because when i++, a will defo == n-i
        output += array[i] * array[(n-i)%n];
    }
    // when any 2 of a,b,c are 0s, 3*(# of 0s) ways to happen
    output += 3 * array[0]; 
    // when all 3 of a,b,c are 0s. 1 way to happen
    output += 1;
    return output;
}

int main(){
    long long i, n, ph, output = 1;
    scanf("%lld", &n);
    // Oh, we will be modifying n, so create a new variable to hold n.
    ph = n;
    // Anyways, we prime factorize n and multiply the results together
    // Why this works is due to Chinese Remainder Theorem
    // Incidentally we don't bother sieving because it wastes time   
    for (i=2; i*i<=ph; ++i){
        if (ph%i == 0){
            // See, i will be the current smallest prime that divides ph
            // We want to find out the smallest prime decomp
            // Hence divide by i all the way until i doesn't divide anymore
            int expo=0;
            while (ph%i == 0){
                expo += 1;
                ph /= i;
            }
            // So because quad residues are multiplicative
            // We can just multiply the prime factors together
            // i.e. output_ab = output_a * output_b
            output *= thething (i, expo);
        }
    }
    // OK we are done with the bulk of the factorizing BUT
    // What if there is still stuff left over in ph? Let's deal with it!
    if (ph != 1){
        output *= thething (ph, 1);
    }
    // So we counted all the ways we can have a^2 + b^2 = c^2 mod (n)
    // This is including when a,b,c=0, and when b > a
    // Let's get rid of those extra solutions

    // First we clean and populate our array:
    for (i=0; i<n; ++i) array[i] = 0;
    // Notice we don't count 0^2 in there. Because it's the trivial value.
    for (i=1; i<n; ++i) ++array[i*i % n];
    // Then get rid of all the zeros:
    output -= zero(n);
    // Notice the grid is symmetric about the main diagonal
    // Hence we add one more copy of the main diagonal and divide 2
    output += diag(n);
    printf ("%lld\n", output/2);
    return 0;
}
