#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) (x > y)?(x):(y)

typedef struct {
    int x;
    int y;
    int z;
} Person;

Person person(int x, int y, int z){
    Person out = {x, y, z};
    return out;
}

int cmpfunc(const void* a, const void * b){
    Person first = *(Person*) a;
    Person second = *(Person*) b;

    if (first.z != second.z) return first.z - second.z;
    if (first.y != second.y) return first.x - second.x;
    return first.x - second.x;
}

Person people [1<<13];

void solve(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        people[i] = person(x, y,z);
    }
    
    // Set up sentinel value:
    people[n] = person(1<<30, 1<<30, 1<<30);

    qsort(people, n, sizeof(Person), cmpfunc);
    int best = -1;
    int numPerson = 0;

    // Sweep through all possible z values
    for (int z = 0; z <= 10000; ++z){

        // Does the person fit the z value?
        while (people[numPerson].z <= z) numPerson++;

        int* satisfied = (int*) calloc(10000, sizeof(int));

        // Now, everyone index < curr fits the z value
        for (int j = 0; j < numPerson; ++j){

            // Suppose we choose some y value. The jth guy will be satisfied if
            // 1) His y value <= the chosen y value
            // 2) His x value <= 10000 - chosen z - chosen y
            // i.e. He will be satisfied between the ranges of [y, 10000- x - z + 1]

            // Oh but we need to make sure x + y can still be satisfied for the
            // currently chosen z value
            if (people[j].y + people[j].x > 10000 - z) continue;

            satisfied[people[j].y]++;
            satisfied[10000 - people[j].x - z + 1]--;
        }

        // Now we just need to find the sweet spot for y given this array
        int curr = 0;
        for (int y = 0; y <= (10000 - z); ++y){
            curr += satisfied[y];
            best = MAX(best, curr);
        }
    }

    printf("%d\n", best); 
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 1; i <= testcases; ++i){
        printf("Case #%d: ", i);
        solve();
    }

    return 0;
}

