#include<stdio.h>
#include<stdlib.h>

double cs[200005], arts[200005];

int cmpfunc(const void* a, const void* b){
    double first = *(double*) a;
    double second = *(double*) b;

    return (first > second) - (second > first);
}

void solve(){
    int numCS, numArts;

    // Scan in input
    scanf("%d %d", &numCS, &numArts);
    double averageCS = 0, averageArts = 0;


    for (int i = 0; i < numCS; ++i){
        scanf("%lf", &cs[i]);
        averageCS += cs[i];
    }
    for (int i = 0; i < numArts; ++i){
        scanf("%lf", &arts[i]);
        averageArts += arts[i];
    }

    // Sort the IQs
    qsort(cs, numCS, sizeof(double), cmpfunc);
    qsort(arts, numArts, sizeof(double), cmpfunc);

    // Find the average iq
    averageCS /= numCS;
    averageArts /= numArts;

    // Find the number of people by linear walk I guess...
    int out = 0;
    for (int i = 0; i < numCS; ++i){
        if (cs[i] >= averageCS) break;
        if (cs[i] > averageArts) out += 1;
    }

    printf("%d\n", out);
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    while (testcases--) solve();
    return 0;
}
