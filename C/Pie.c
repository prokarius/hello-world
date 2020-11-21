#include<stdio.h>
#include<math.h>

#define PI 3.14159265358979323846
#define EPSILON 1e-6

double pi[1<<14];

void solve(){
    // Scan in input
    int n, f;
    scanf ("%d %d", &n, &f);
    f++; // I want some pie too

    for (int i = 0; i < n; ++i){
        double r;
        scanf("%lf", &r);
        pi[i] = PI * r * r;
    }

    // Binary search for the answer
    double lo = 0;
    double hi = 1e10;
    double mid;

    while(hi - lo > EPSILON){
        mid = (hi + lo) / 2;
        double count = 0;

        for (int i = 0; i < n; ++i){
            count += floor(pi[i] / mid);
        }
    
        if (count >= f) lo = mid;
        else hi = mid;
    }

    printf("%lf\n", mid);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    while(testcases--) solve();

    return 0;
}

