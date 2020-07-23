#include<stdio.h>
#include<math.h>

#define MIN(x, y) (x<y)?(x):(y)

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // This is the amount of tape we saved.
    double total = 0;

    double longSide = pow(2, -0.75);

    long long required = 1; // We need one A1 paper
    long long kept = 0;
    int size;

    // We begin with A2 paper
    for (size = 2; size <= n; ++size){
        // Double the number of required papers at this length
        required <<= 1;

        // Double the number of papers we had. And keep the tape!
        total += kept * longSide;
        kept <<= 1;

        int numPaper;
        scanf("%d", &numPaper);

        // Split the papers and save the imaginary tape that held the papers together
        required -= numPaper;

        kept += MIN(numPaper, required);

        // Have we enough papers?
        if (required <= 0) break;

        longSide /= pow(2, 0.5);
    }

    // Short circuit: Do we have required?
    if (required > 0){
        printf("impossible\n");
        return 0;
    }

    // Great we are done with the loops. 
    double side = pow(2, -0.75);

    double tapeRequired = 0;
    for (int i = 0; i < size-1; ++i){
        tapeRequired += side * (1 << i);
        side /= sqrt(2);
    }

    // Print out the tape required
    printf("%lf\n", tapeRequired - total);

    return 0;
}
