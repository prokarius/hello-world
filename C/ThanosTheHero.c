#include<stdio.h>

int population[65536];

int main(){
    int n;

    // Scan in input
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &population[i]);
    }

    // Add a sentinel value
    population[n] = 1<<30;

    long long out = 0;

    for (int i = n-1; i >= 0; --i){
        if (population[i] < population[i+1]) continue;
        int tokill = population[i] - (population[i+1]-1);
        out += tokill;
        population[i] = population[i] - tokill;
    }

    // Check if we killed too many people
    if (population[0] < 0){
        printf("1\n");
        return 0;
    }

    printf("%lld\n", out);
    return 0;
}

