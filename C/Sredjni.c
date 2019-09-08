#include<stdio.h>

int input[100005];
int numAbove[100005];

int main(){
    // Scan in input
    int n, b;
    int middle;
    scanf("%d %d", &n, &b);

    for (int i = 0; i < n; ++i){
        scanf("%d", &input[i]);

        // Find the index that the median element is at
        if (input[i] == b){
            middle = i;
        }
    }

    // From the input itself, find the distribution of numbers to the right
    // If we have 2 numbers to the right of the pivot, one is higher, and one is lower
    // Then if LHS balances out, there are 2 choices for where the right side ends
    int frequency = middle;
    for (int i = middle+1; i < n; ++i){
        (input[i] > b)?(frequency++):(frequency--);
        ++numAbove[frequency];
    }

    // We can end at the middle thing itself too!
    ++numAbove[middle];

    // Now start from the left, and add up the numbers!
    long long output = 0;
    int diff = 0;
    for (int i = middle-1; i >= 0; --i){
        (input[i] > b)?(diff++):(diff--);
        output += numAbove[middle-diff];
    }

    // Oh don't forget that we can start at the middle too!
    output += numAbove[middle];

    // PRINT THAT SHIT!
    printf("%lld\n", output);

    return 0;
}

