#include<stdio.h>
#include<stdlib.h>

int cmpfunc(const void* a, const void* b){
    return(*(int*)a - *(int*)b);
}

int main(){
    int n, k;
    int event[200005];
    scanf("%d %d", &n, &k);

    // For every event, push it and the finish processing event into the queue
    for (int i = 0; i < n; ++i){
        int request;
        scanf("%d", &request);
        event[2*i] = 2 * request + 1;
        event[2*i + 1] = 2 * (request + 1000);
    }

    // Sort the event queue
    qsort(event, 2*n, sizeof(int), cmpfunc);

    // Each time we meet a start event, we add to count
    // Each time we meet a end event, we subtract from count
    int count = 0;
    int max = -1;
    for (int i = 0; i < 2*n; ++i){
        if (event[i] & 1){
            ++count;
            if (count > max) max = count;
        }
        else --count;
    }

    // Divide it by the number of requests per server
    printf("%d\n", (k + max - 1) / k);
    return 0;
}