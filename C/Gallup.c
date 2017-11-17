#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define EPSILON 1e-8

double array[21], guess[21][2];

int cod(int n, int prec){
    int power = 1, l = prec - 2;
    double invpower = 0.5;
    while (prec--) power *= 10;
    while (l--) invpower /= 10;
    int res = 1;
    // Slowly walk up, and see if the number makes sense
    for (; res < 10001; ++res){
        int i = 0, flag = 0, maxtotes = 0, mintotes = 0;
        for (; i < n; ++i){
            // Find the min number of people that could have answered here
            guess[i][0] = ceil((array[i]-invpower)*res/100);
            mintotes += guess[i][0];

            // Find the max number of people that could have answered here
            // If the answer is an integer, subtract one from it.
            guess[i][1] = (array[i]+invpower)*res/100;
            if (fabs(guess[i][1] - (int)(guess[i][1] + EPSILON)) < EPSILON) guess[i][1] -= 0.5;
            guess[i][1] = floor(guess[i][1]);
            maxtotes += guess[i][1];

            // Now, if any of the range of guesses are off from the given value
            // Set a flag and break. This is not the value we are looking for
            if (round((guess[i][0]/res)*100*power)/power > array[i] &&
                round((guess[i][1]/res)*100*power)/power < array[i]){
                ++flag;
                break;
            }
        }

        // If the flag is not triggered, and res is in range of possible answers
        // Return it. Else return 0.
        if (!flag && mintotes <= res && res <= maxtotes) return res;
    }
    return 0;
}

int main(){
    int n, casenum = 0, it;
    scanf("%d", &n);
    while (n){
        // Scan the first input into a thing
        // This will be used to find the precision
        char buffer[15];
        scanf(" %s", buffer);
        int len = strlen(buffer);

        // This is what line 41 does actually:
        // for (it = len-1; it > 0; --it) {
        //     if (buffer[it] == '.') break;
        // }
        for (it = len - 1; buffer[it] != '.' && it > 0; --it);
        if (it != 0) it = len-it-1;

        array[0] = strtod(buffer, NULL);
        // Scan the rest of the inputs
        int k=0;
        while (++k<n){
            double t;
            scanf("%lf", &t);
            array[k] = t;
        }

        printf("Case %d: ", ++casenum);
        int result = cod(n, it+2);
        if (result) printf("%d\n", result);
        else printf("error\n");
        scanf ("%d", &n);
    }
    return 0;
}
