#include<stdio.h>
#include<stdlib.h> 
#include<math.h>

double houses[256];
double plots[256];

int cmpfunc(const void* a, const void* b){
    double first = *(double*) a;
    double second = *(double*) b;
    return (first < second) - (second < first);
}

int main(){
    // Scan in input
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; ++i){
        scanf("%lf", &plots[i]);
    }

    for (int i = 0; i < m; ++i){
        scanf("%lf", &houses[i]);
    }

    for (int i = m; i < m+k; ++i){
        double in;
        scanf("%lf", &in);
        in /= sqrt(2);
        houses[i] = in;
    }

    // Sort
    qsort(plots, n, sizeof(double), cmpfunc);
    qsort(houses, m+k, sizeof(double), cmpfunc);

    // Greedily assign houses to the biggest plots
    int houseptr = 0;
    int plotptr = 0;
    int out = 0;

    while (houseptr < m+k){
        if (plots[plotptr] > houses[houseptr]){
            out++;
            plotptr++;
        }
        houseptr++;
    }

    printf("%d\n", out);

    return 0;
}

