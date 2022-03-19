#include<stdio.h>

int first[128];
int second[128];
int secondCopy[128];

int MAX(int x, int y){
    return x > y ? x : y;
}

int main(){
    int n;
    int a, b;

    // Scan in input
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d %d", &a, &b);

        // Store the count numbers into the two lists
        first[a]++;
        second[b]++;

        // Maybe we can just do a deep copy, simplifies our lives...
        for (int j = 0; j <= 100; ++j){
            secondCopy[j] = second[j];
        }

        // Start from the top of a, and count downwards.
        // Greedily match the counts of numbers.
        int best = -1;
        int currentB = 101;

        for (int j = 0; j <= 100; ++j){
            int num_remain = first[j];
            while (num_remain != 0){
                if (secondCopy[currentB] == 0){
                    currentB--;
                    continue;
                }
                best = MAX(best, (j + currentB));

                if (num_remain > secondCopy[currentB]){
                    num_remain -= secondCopy[currentB];
                    currentB--;
                    continue;
                }

                secondCopy[currentB] -= num_remain;
                num_remain = 0;
            }
        }

        // Print the best
        printf("%d\n", best);
    }
}

