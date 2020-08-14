#include<stdio.h>

int ghettoLinkedListPrev[1<<19];
int ghettoLinkedListNext[1<<19];

// Move the number x to in front of y
void A(int x, int y){
    int xPrev = ghettoLinkedListPrev[x];
    int xNext = ghettoLinkedListNext[x];

    // Remove x
    ghettoLinkedListNext[xPrev] = xNext;
    ghettoLinkedListPrev[xNext] = xPrev;

    int yPrev = ghettoLinkedListPrev[y];

    // Put x in front of y
    ghettoLinkedListNext[yPrev] = x;
    ghettoLinkedListPrev[y] = x;
    ghettoLinkedListNext[x] = y;
    ghettoLinkedListPrev[x] = yPrev;
}

// Move the number x to after y
void B(int x, int y){
    int xPrev = ghettoLinkedListPrev[x];
    int xNext = ghettoLinkedListNext[x];

    // Remove x
    ghettoLinkedListNext[xPrev] = xNext;
    ghettoLinkedListPrev[xNext] = xPrev;

    int yNext = ghettoLinkedListNext[y];

    // Put x after y
    ghettoLinkedListNext[y] = x;
    ghettoLinkedListPrev[yNext] = x;
    ghettoLinkedListNext[x] = yNext;
    ghettoLinkedListPrev[x] = y;
}

int LIS[1<<19];
int LISIndex[1<<19];
int prev[1<<19];
int array[1<<19];

int main(){
    // Scan in input
    int n, m;
    scanf("%d %d", &n, &m);

    // Create the LinkedList
    for (int i = 0; i <= n+1; ++i){
        ghettoLinkedListPrev[i] = i-1;
        ghettoLinkedListNext[i] = i+1;
    }

    // Scan in the moves and actually move them
    for (int i = 0; i < m; ++i){
        int x, y;
        char move;

        scanf(" %c %d %d", &move, &x, &y);

        if (move == 'A') A(x, y);
        else B(x, y);
    }

    // Recover the array
    int curr = 0;
    for (int i = 0; i < n; ++i){
        curr = ghettoLinkedListNext[curr];
        array[i] = curr;
    }

    // Initialize the LIS array:
    for (int i = 0; i < n; ++i){
        LIS[i] = 1<<30;
    }
    LISIndex[0] = -1;

    // Do LIS
    int LISLength = 0;

    for (int i = 0; i < n; ++i){
        
        // Binary Search for where to insert LIS
        int lo = 0;
        int hi = LISLength;

        while (lo < hi){
            int mid = (lo + hi) / 2;
            if (LIS[mid] < array[i]){
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }

        // If we are at the end, increase LISLength:
        if (hi == LISLength){
            LISLength++;
        }

        LIS[hi] = array[i];
        LISIndex[hi+1] = i;
        prev[i] = LISIndex[hi];
    }

    // The number of statements that needs to change is n - length of LIS
    printf("%d\n", n - LISLength);

    // Regenerate the stuff back
    curr = LISIndex[LISLength];
    int count = LISLength - 1;
    while (curr != -1){
        LIS[count] = curr;
        curr = prev[curr];
        count--;
    }

    // Now we have the longest increasing sequence, we can re-create the sequence
    // OK now to generate the B statements:
    int arrayptr = 1;
    int LISptr = 0;
    while (arrayptr <= n && LISptr < LISLength){
        if (array[LIS[LISptr]] == arrayptr){
            LISptr++;
        }
        else {
            printf("A %d %d\n", arrayptr, array[LIS[LISptr]]);
        }
        arrayptr++;
    }

    // Lastly, we need B moves if LIS does not include n
    arrayptr = array[LIS[LISLength-1]];
    while (arrayptr < n){
        printf("B %d %d\n", arrayptr+1, arrayptr);
        arrayptr++;
    }

    return 0;
}

