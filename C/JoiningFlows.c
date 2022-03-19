#include<stdio.h>
#include<stdlib.h>

#define EPSILON 1e-6

typedef struct {
    int lo;
    int hi;
    double temp;
} Faucet;

int cmpfunc(const void* a, const void* b){
    return (*(Faucet*)a).temp > (*(Faucet*)b).temp ? 1 : -1;
}

Faucet faucets[10];

Faucet faucet(int lo, int hi, double temp){
    Faucet new;
    new.lo = lo;
    new.hi = hi;
    new.temp = temp;
    return new;
}

int main(){
    // Scan in input
    int k, r;
    int baseFlow = 0;
    double baseWeight = 0;
    scanf ("%d", &k);
    for (int i = 0; i < k; ++i){
        int lo, hi;
        double temp;
        scanf("%lf %d %d", &temp, &lo, &hi);
        faucets[i] = faucet(lo, hi, temp);
        baseFlow += lo;
        baseWeight += lo * temp;
    }

    // Sort the faucets by temperature
    qsort(faucets, k, sizeof(Faucet), cmpfunc);

    // Find the lowest and highest temperature for each query by greedy
    // If the required temp is in the range, output yes
    scanf("%d", &r);
    for (int i = 0; i < r; ++i){
        int reqTemp, reqFlow;
        scanf("%d %d", &reqTemp, &reqFlow);

        // Guard: if RequiredFlow is too big, give up
        if (reqFlow < baseFlow){
            printf("no\n");
            continue;
        }

        // Greedily select the lowest to highest
        double lowestTemp = baseWeight;
        double highestTemp = baseWeight;
        int flowLeft = reqFlow - baseFlow;
        for (int i = 0; i < k; ++i){
            int delta = faucets[i].hi - faucets[i].lo;
            if (delta > flowLeft){
                lowestTemp += flowLeft * faucets[i].temp;
                flowLeft = 0;
                break;
            }
            lowestTemp += delta * faucets[i].temp;
            flowLeft -= delta;
        }

        // Sanity: if we need too much flow, return False
        if (flowLeft > 0){
            printf("no\n");
            continue;
        }

        flowLeft = reqFlow - baseFlow;
        for (int i = k-1; i >= 0; --i){
            int delta = faucets[i].hi - faucets[i].lo;
            if (delta > flowLeft){
                highestTemp += flowLeft * faucets[i].temp;
                flowLeft = 0;
                break;
            }
            highestTemp += delta * faucets[i].temp;
            flowLeft -= delta;
        }

        // If we are in range, print yes, else no
        lowestTemp /= reqFlow;
        highestTemp /= reqFlow;
        if (lowestTemp < reqTemp + EPSILON 
                && reqTemp < highestTemp + EPSILON){
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
    }

    return 0;
}
