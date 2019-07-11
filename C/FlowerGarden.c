#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct{
    double x;
    double y;
} Plant;

// Constructor
Plant plant(double x, double y){
    Plant out;
    out.x = x;
    out.y = y;
    return out;
}

double distance(Plant first, Plant second){
    double dx = first.x - second.x;
    double dy = first.y - second.y;
    return sqrt(dx*dx + dy*dy);
}

int primes[30001];

void solve(){
    // Scan in input
    int n;
    double d;
    scanf("%d %lf", &n, &d);

    Plant* flowers = (Plant*) malloc((n+1) * sizeof(Plant));

    for (int i = 0; i < n; ++i){
        double x, y;
        scanf ("%lf %lf", &x, &y);
        flowers[i] = plant(x, y);
    }

    // Put a sentinel flower
    flowers[n] = plant(1e10, 1e10);

    int out = 1;
    d -= distance(flowers[0], plant(0, 0));
    while (d > -1e-7){
        d -= distance(flowers[out], flowers[out - 1]);
        ++out;
    }

    // Now find the smallest "prime" number below out
    out--;
    while (primes[out] != 1){
        out--;
    }

    // Print it out
    printf("%d\n", out);

    // Don't forget to free
    free(flowers);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    // Generate the prime numbers
    for (int i = 2; i < 30000; ++i){
        primes[i] = 1;
    }

    for (int i = 2; i < 30000; ++i){
        if (primes[i] != 1) continue;
        for (int j = 2*i; j < 30000; j += i){
            primes[j] = 0;
        }
    }

    primes[0] = 1;

    while (testcases--){
        solve();
    }

    return 0;
}
