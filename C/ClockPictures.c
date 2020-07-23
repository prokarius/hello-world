#include<stdio.h>
#include<stdlib.h>

int hands1[400005];
int hands2[200005];
int LPS[200005];

int cmpfunc(const void* a, const void* b){
    int first = *(int*) a;
    int second = *(int*) b;
    return first - second;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // Scan in first set of hands
    for (int i = 0; i < n; ++i){
        int angle;
        scanf("%d", &angle);
        hands1[i] = angle;
        hands1[i+n] = angle + 360000;
    }

    // Scan in second set of hands
    for (int i = 0; i < n; ++i){
        int angle;
        scanf("%d", &angle);
        hands2[i] = angle;
    }

    // Sort both lists.
    qsort(hands1, 2*n, sizeof(int), cmpfunc);
    qsort(hands2, n, sizeof(int), cmpfunc);

    // For circular
    hands2[n] = hands2[0] + 360000;

    // Find the angles between consequetive hands.
    for (int i = 0; i < 2*n; ++i){
        hands1[i] = hands1[i+1] - hands1[i];
    }

    for (int i = 0; i < n; ++i){
        hands2[i] = hands2[i+1] - hands2[i];
    }

    // Now we do KMP
    // Set up LPS array
    LPS[0] = 0;
    int i = 1;
    int prefix = 0;

    while (i <= n){
        if (hands2[i] == hands2[prefix]){
            ++prefix;
            LPS[i++] = prefix;
        }
        else if (prefix != 0){
            prefix = LPS[prefix-1];
        }
        else {
            LPS[i] = 0;
            ++i;
        }
    }

    // Do the actual string check
    int flag = 0;
    
    int word = 0;
    int target = 0;

    while (word < 2*n){
        if (hands1[word] == hands2[target]){
            word++;
            target++;

            if (target == n){
                flag = 1;
                break;
            }
        }
        else if (target != 0){
            target = LPS[target-1];
        }
        else {
            word++;
        }
    }

    printf(flag?"":"im");
    printf("possible\n");

    return 0;
}
