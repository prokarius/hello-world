#include<stdio.h>

// Is the run function.
int anti(int n){
    int array[10005];
    int visited[10005];

    // Reset array
    for (int i=0; i<n; ++i){
        array[i] = 0;
        visited[i] = 0;
    }

    // Scan in input
    for (int i=0; i<n; ++i){
        scanf("%d", &array[i]);
    }

    // i is the first number
    // j is the second number
    // k is the third number, given by 2*j - i
    for (int j=0; j<n; ++j){
        visited[array[j]] = 1;
        for (int i=0; i<j; ++i){
            int k = 2*array[j] - array[i];
            // If k is out of bounds, continue
            // If we have not seen k before, then it is to the right of the 2nd
            // number. Hence it is anti arithmetic.
            if (k < 0 | k >= n) continue;
            if (!visited[k]) return 0;
        }
    }
    return 1;
}

int main(){
    int n;
    while (1) {
        // Scan the n, and get rid of the colon.
        scanf("%d%*c ", &n);
        if (n==0) return 0;

        printf("%s\n", anti(n) ? "yes" : "no");
    }
}


// Old TLE Solution

/*
#include<stdio.h>

int main(){
    int array [10005], array2[10005], n, i, j, c;
    while (1) {
        int flag = 0;
        scanf("%d%*c ", &n);
        if (n==0) return 0;
        for (i=0; i<n; i++){
            scanf("%d ", &array[i]);
        }
        for (i=0; i<n; i++){
            array2[array[i]] = i;
        }
        for (i=0;i<n-1; i++){
            if (flag) break;
            for (j=i+1; j<n; j++){
                c = 2*array[j]-array[i];
                if (c < 0 || c >= n) continue;
                if (array2[c] > j){
                    flag = 1;
                    break;
                }
            }
        }
        printf("%s\n", flag ? "no" : "yes");
    }
}
*/
