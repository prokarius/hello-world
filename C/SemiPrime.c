#include<stdio.h>
#include<math.h>

int main(){
    int h;
    int count[250005]; // Stores the number of H numbers below it
    int divisor[250005]; // Stores the number of divisors

    // We need to do some preprocessing first, then we can do O(1) queries
    // This is an iterative dp problem.
    // H-number with a value of n is stored at (n-1)/4

    count[0] = 0; // Initialise for the 0th H-number (which is 1).

    // For each H number below 1M (i is a h number, which is the ath H-number)
    for (int i=5, a=1; i<1000002; i+=4, a++){
        int notfound = 1;

        // We will do trail division.
        // Calculate sqrt i and iterate. (j is a h number, which is the bth H-number)
        int max = (int) sqrt(i);
        for (int j=5, b=1; j<=max; j+=4, b++){

            // If j divides into i, then we break out of the inner loop.
            // Then we say the number of divisors of the current number is equal
            // to 1 + the number of divisors of that factor number
            // Note that we need to set a flag if this happens.
            if (i%j == 0){
                notfound = 0;
                divisor[a] = divisor[(i/j)/4] + 1;
                break;
            }
        }

        // So if we have not found a divisor, then we say it's a H prime.
        if (notfound){
            divisor[a] = 1;
        }

        // Lastly, we need to update our count
        count[a] = count[a-1];
        if (divisor[a] == 2){
            ++count[a];
        }
    }

    // Our preprocessing down, we can start scanning numbers:
    int n;
    scanf("%d", &n);

    while (n){
        printf ("%d %d\n", n, count[n/4]);
        scanf("%d", &n);
    }
    return 0;
}
