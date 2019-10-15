#include<stdio.h>

int prince[1<<16];
int princess[1<<16];
int mapping[1<<16];
int LIS[1<<16];

void solve(int testcaseNum){
    // Scan in input
    int n, p, q;
    scanf("%d %d %d", &n, &p, &q);

    // Reset the mapping and LIS array
    for (int i = 0; i <= n*n; ++i){
        mapping[i] = 0;
        LIS[i] = 1<<30;
    }

    for (int i = 0; i <= p; ++i){
        scanf("%d", &prince[i]);
    }

    for (int i = 0; i <= q; ++i){
        scanf("%d", &princess[i]);
    }

    // OK make the mapping
    // Now prince[i] can be transformed into an increasing sequence!
    for (int i = 0; i <= p; ++i){
        mapping[prince[i]] = i+1;
    }

    // Convert the princess array into the sequence
    for (int i = 0; i <= q; ++i){
        princess[i] = mapping[princess[i]];
    }

    // Lastly, find the LIS of the array
    int LISLength = 0;

    for (int i = 0; i <= q; ++i){
        int lo = 0;
        int hi = LISLength;
        while (lo < hi){
            int mid = (lo + hi)/2;
            if (LIS[mid] < princess[i]){
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }

        LIS[hi] = princess[i];
        if (hi == LISLength){
            LISLength++;
        }
    }

    printf("Case %d: %d\n", testcaseNum, LISLength);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 1; i <= testcases; ++i){
        solve(i);
    }

    return 0;
}
