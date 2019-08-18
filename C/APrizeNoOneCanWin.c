#include<stdio.h>
#include<stdlib.h>

int cost[100005];

int cmpfunc(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int main(){
    int n, price;
    scanf("%d %d", &n, &price);

    // Guard clause. If there is only 1 item, mark it for sale
    if (n == 1){
        printf("1\n");
        return 0;
    }

    for (int i = 1; i <= n; ++i){
        scanf("%d", &cost[i]);
    }

    // Sort the items
    qsort(cost, n+1, sizeof(int), cmpfunc);

    // Select at least 1 item
    int i = 1;
    for (; i < n; ++i){
        if (cost[i] + cost[i+1] > price) break;
    }

    printf("%d\n", i);

    return 0;
}
