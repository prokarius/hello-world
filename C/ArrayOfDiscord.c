#include<stdio.h>

int n;
long long array[128];

int notSorted(int index, int digit, long long decimal){
    if (array[index] < decimal) return 0;  // Not big enough
    long long new_num = array[index] / (10 * decimal);
    
    // Sanity check, did we change the leading digit to a zero?
    if ((digit == 0) && (new_num == 0) && array[index] > 9) return 0;
    new_num = new_num * (10 * decimal) + digit * decimal + array[index] % decimal;

    // Check left and right
    if (array[index - 1] > new_num || array[index + 1] < new_num){
        array[index] = new_num;
        for (int i = 1; i <= n; ++i){
            printf("%lld ", array[i]);
        }
        printf("\n");
        return 1;
    }
    return 0;
}

int main(){
    // Scan in input
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i){
        scanf("%lld", &array[i]);
    }

    // Add sentinel values
    array[0] = -1;
    array[n+1] = 1LL<<60;

    // I think we can just brute force?
    for (int i = 1; i <= n; ++i){
        for (int j = 0; j < 10; ++j){
            for (long long k = 1; k < 1LL<<50; k *= 10){
                if (notSorted(i, j, k)){
                    return 0; // Printed in the function
                }
            }
        }
    }

    printf("impossible\n");

    return 0;
}

