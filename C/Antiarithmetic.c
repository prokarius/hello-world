// Note that each integer appears only once.
// Hence, we can just index the

#include<stdio.h>

int main(){
    int array [10005], array2[10005], n, i, j, c;
    while (1) {
        int flag = 0;

        // Scan the n, and get rid of the colon. Scan into an array
        scanf("%d%*c ", &n);
        if (n==0) return 0;
        for (i=0; i<n; i++){
            scanf("%d ", &array[i]);
        }

        // Then store the index in another array
        for (i=0; i<n; i++){
            array2[array[i]] = i;
        }

        // For each pair of ints, if the 3rd member is found after 2nd => Anti.
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
