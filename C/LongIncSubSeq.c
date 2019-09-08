#include<stdio.h>

int input[100005];
int LIS[100005];
int LISIndex[100005];
int prev[100005];
int arr[100005];

void solve(int n){
    // Scan in input
    for (int i = 0; i < n; ++i){
        scanf("%d", &input[i]);
    }

    // Reset the LIS array
    for (int i = 0; i < n; ++i){
        LIS[i] = 1<<30;
    }
    LISIndex[0] = -1;

    // Do LIS
    int LISLength = 0;
    for (int i = 0; i < n; ++i){

        // Binary search for where to insert the LIS
        int lo = 0;
        int hi = LISLength;
        while (lo < hi){
            int mid = (lo + hi) / 2;
            if (LIS[mid] < input[i]){
                lo = mid+1;
            }
            else {
                hi = mid;
            }
        }

        // hi contains the correct index
        if (hi == LISLength){
            LISLength++;
        }

        LIS[hi] = input[i];
        LISIndex[hi+1] = i;
        prev[i] = LISIndex[hi];
    }

    // Get the stuff back
    printf("%d\n", LISLength);
    int curr = LISIndex[LISLength];
    int count = LISLength - 1;
    while (curr != -1){
        arr[count] = curr;
        curr = prev[curr];
        --count;
    }

    printf("%d", arr[0]);
    for (int i = 1; i < LISLength; ++i){
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main(){
    int n;

    // Scan until EOF
    while(scanf("%d", &n) != EOF){
        solve(n);
    }

    return 0;
}
