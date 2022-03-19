#include<stdio.h>

long long maxArray[1<<19];
long long sumArray[1<<19];
long long sum = 0;

long long MAX(long long x, long long y){ return x > y ? x : y; }
long long MIN(long long x, long long y){ return x < y ? x : y; }

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // Start with all the paths patrolled by one police.
    // For each node, try to combine officers from two paths ending in that node
    // Note that we can only combine officers up to the sum of officers coming from
    // the non-maximum paths
    for (int i = 1; i < n; ++i){
        int u, v, p;
        scanf("%d %d %d", &u, &v, &p);
        sum += p;
        sumArray[u] += p;
        maxArray[u] = MAX(maxArray[u], p);
        sumArray[v] += p;
        maxArray[v] = MAX(maxArray[v], p);
    }

    for (int i = 0; i < n; ++i){        
        sum -= MIN(sumArray[i] / 2, sumArray[i] - maxArray[i]);
    }

    printf("%lld\n", sum);
}

