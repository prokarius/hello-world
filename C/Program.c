#include<stdio.h>

long long array[1000005];
long long final[1000005];
long long prefix[1000005];

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; ++i){
        int input;
        scanf("%d", &input);
        array[input]++;
    }

    // Step through all the input, and simulate the something function
    for (int i = 2; i < 1000005; ++i){
        if (array[i]){
            for (int j = 0; j < n; j += i){
                final[j] += array[i];
            }
        }
    }

    // Create the prefix sums:
    prefix[0] = 0;
    for (int i = 1; i <= n; ++i){
        prefix[i] = prefix[i-1] + final[i-1];
    }

    // Process the queries:
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        long long out = prefix[end+1] - prefix[start] + (end-start+1)*array[1];
        printf("%lld\n", out);
    }
    return 0;
}
