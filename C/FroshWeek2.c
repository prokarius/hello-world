#include<stdio.h>
#include<stdlib.h>

int frees[200005];
int tasks[200005];

int cmpfunc(const void* a, const void* b){
    return *(int*) b - *(int*) a;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    // Scan in input
    for (int i = 0; i < n; ++i){
        int taskTime;
        scanf("%d", &taskTime);
        tasks[i] = taskTime;
    }

    for (int i = 0; i < m; ++i){
        int freeTime;
        scanf("%d", &freeTime);
        frees[i] = freeTime;
    }

    // Sort the tasks in decreasing order
    qsort(tasks, n, sizeof(int), cmpfunc);
    qsort(frees, n, sizeof(int), cmpfunc);

    int currWork = 0;
    int output = 0;

    // Process the time in decreasing order
    // Assign the longest work currently possible to the time
    for (int i = 0; i < m; ++i){
        if (currWork == n) break;
        while (frees[i] < tasks[currWork]){
            currWork++;
            if (currWork == n) break;
        }
        if (currWork == n) break;

        // We have found the longest task that can fit in this slot.
        // Do the task and move on to the next slot
        output++;
        currWork++;
    }

    // Print output
    printf("%d\n", output);

    return 0;
}

