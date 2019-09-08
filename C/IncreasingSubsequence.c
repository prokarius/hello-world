#include<stdio.h>

int input[256];
int prev[256];
int LIS[256];
int LISIndex[256];
int arr[256];

void solve(int n){
    // Scan in input
    for (int i = 0; i < n; ++i){
        scanf("%d", &input[i]);
    }

    // Reset the LIS array
    for (int i = 0; i < 256; ++i){
        LIS[i] = 1<<30;
    }
    LISIndex[0] = -1;

    int len = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j <= len; ++j){
            if (LIS[j] >= input[i]){
                if (j == len) len++;
                LIS[j] = input[i];
                LISIndex[j+1] = i;
                prev[i] = LISIndex[j];
                break;
            }
        }
    }

    // Print that shit
    printf("%d", len);
    int curr = LISIndex[len];
    int count = len-1;
    while (curr != -1){
        arr[count] = input[curr];
        curr = prev[curr];
        count--;
    }

    for (int i = 0; i < len; ++i){
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);

    while (n){
        solve(n);
        scanf("%d", &n);
    }

    return 0;
}
