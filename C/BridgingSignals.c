#include<stdio.h>

int input[1<<19];
int LIS[1<<19];

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &input[i]);
        LIS[i] = 1<<30;
    }

    // Do LIS
    int best = 0;
    LIS[0] = -1;

    for (int i = 0; i < n; ++i){
        int lo = 0;
        int hi = best;

        while (lo < hi){
            int mid = (lo + hi)/2;
            if (LIS[mid] < input[i]){
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }

        if (hi == best){
            best++;
        }

        LIS[hi] = input[i];
    }

    // Print that shit
    printf("%d\n", best);

    return 0;
}

