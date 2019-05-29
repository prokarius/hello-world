#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INF (1LL << 60)

char* names[16];
int cannot[16][16];
long long dp[1 << 11][16];
int out[16];
int n;

int cmpfunc(const void* a, const void* b){
    char** firstStr = (char**) a;
    char** secondStr = (char**) b;
    return strcmp(*firstStr, *secondStr);
}

long long MIN(long long x, long long y){
    return (x < y)?(x):(y);
}

int findName (char* name){
    for (int i = 0; i < n; ++i){
        if (strcmp(name, names[i]) == 0){
            return i;
        }
    }

    // WTF this is not supposed to happen
    return 0xDEADBEEF;
}

void run(){

    // Reset the cannot array
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cannot[i][j] = 0;
        }
    }

    // Also reset the bitmask:
    for (int i = 0; i < (1 << n); ++i){
        for (int j = 0; j < n; ++j){
            dp[i][j] = INF;
        }
    }

    char* name;

    // Scan in input
    for (int i = 0; i < n; ++i){
        name = (char*) malloc(32 * sizeof(char));
        scanf("%s", name);
        names[i] = name;
    }

    // Sort the names
    qsort(names, n, sizeof(char**), cmpfunc);

    // Scan in the names of the people that cannot get along
    char* start = (char*) malloc(32 * sizeof(char));
    char* end = (char*) malloc(32 * sizeof(char));
    int m;

    scanf("%d", &m);

    for (int i = 0; i < m; ++i){
        scanf("%s %s", start, end);
        int first = findName(start);
        int second = findName(end);

        cannot[first][second] = 1;
        cannot[second][first] = 1;
    }

    // Initialise the dp Matrix
    for (int i = 0; i < n; ++i){
        dp[1<<i][i] = i;
    }

    // Yay! Lets do bitmasking
    // Note that dp[i][j] represents the ith bitmask was filled and the last member
    // to go in was person j
    for (int bitmask = 1; bitmask < (1 << n); ++bitmask){
        for (int person = 0; person < n; ++person){

            // If we realise we cannot make it here, just give up
            if (dp[bitmask][person] == INF) continue;

            // If not, try to populate with the next person
            for (int nextPerson = 0; nextPerson < n; ++nextPerson){

                // If we have seen this person before, give up
                if (bitmask & (1 << nextPerson)) continue;

                // If the current guy cannot work with the new guy, give up
                if (cannot[person][nextPerson]) continue;

                // Set the bitmask
                dp[bitmask ^ (1 << nextPerson)][nextPerson] = MIN(
                        dp[bitmask ^ (1 << nextPerson)][nextPerson],
                        (dp[bitmask][person] * 16) + nextPerson);
            }
        }
    }

    // OK we have reached the end, now to print the best
    long long best = INF;

    for (int i = 0; i < n; ++i){
        if (dp[(1<<n)-1][i] != INF){
            best = MIN(best, dp[(1<<n)-1][i]);
        }
    }

    // Have we found something?
    if (best == INF){
        printf("You all need therapy.");
    }
    else {
        for (int i = n-1; i >= 0; --i){
            out[i] = best % 16;
            best /= 16;
        }

        // Print out the names
        printf("%s", names[out[0]]);
        for (int i = 1; i < n; ++i){
            printf(" %s", names[out[i]]);
        }
    }

    printf("\n");

    // Free all the memory:
    for (int i = 0; i < n; ++i){
        free(names[i]);
    }

    free(start);
    free(end);
}

int main(){

    while (scanf("%d", &n) != EOF){
        run();
    }

    return 0;
}
