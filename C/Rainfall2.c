#include<stdio.h>
#include<math.h>

int main(){
    double L, K, T1, T2, H;
    scanf("%lf %lf %lf %lf %lf", &L, &K, &T1, &T2, &H);

    // Edge case 1: H < L. No leak.
    if (H < L){
        printf("%lf %lf\n", H, H);
        return 0;
    }

    // Case 2: H > L
    // Suppose it takes time x = L/F to get the the leak
    // Then for the rest of (T1 - x), it fills at rate F-K
    // And then it leaks T2*K amount.
    // So we have (L + (T1 - L/F)*(F-K) - T2*K) = H
    // (T1 - L/F)*(F-K) = H - L + T2*K
    // Let q = H - L + T2*K > 0
    // T1*F - L - T1*K + L*K/F = q
    // T1*F^2 - (L + T1*K + q)F + L*K = 0
    // Solve to get F, multiply by T1 to get total rainfall
    double q = H - L + T2*K;
    double a = T1;
    double b = -(L + T1*K + q);
    double c = L*K;

    double delta = sqrt(b*b - 4*a*c);
    double F = (-b + delta) / (2*a);
    double hi = F*T1;

    // Edge case 3: If H == L, then the least amount of rainfall is H
    double lo = (L == H ? H: hi);

    printf("%lf %lf\n", lo, hi);
    return 0;
}

