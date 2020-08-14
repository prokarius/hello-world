#include<stdio.h>
#include<stdlib.h>

#define MIN(x, y) (x<y)?(x):(y)

int cmpfunc(const void* a, const void* b){
    return *(int*)a > *(int*) b;
}

int* tracks; // Stores where the track positions are
int* marks; // Stores all the marks
int* memo;
int n, m;


int bit_index(int bit) {
  return __builtin_ctz(bit);
}

// DP bitmask returns min # of unicycles to make bitmask marks
int dp(int bitmask){
    // Have we used up all the marks?
    if (bitmask == 0) return 0;

    // Have we been here before?
    if (memo[bitmask] != 0) return memo[bitmask];

    // Well he could be alone
    int nextUnicycle = (bitmask & -bitmask);
    int best = dp(bitmask ^ nextUnicycle) + 1;
    
    // Or two of the marks could be made from one unicycle
    int curr = bit_index(nextUnicycle);
    for (int i = curr+1; i < n; ++i){
        int possible = 1;
        int newBitmask = (bitmask - nextUnicycle) & (1023 - (1<<i));
        int difference = tracks[i] - tracks[curr];

        // Would the unicycle that made this pair of marks make any other marks
        // below it?
        int lopos = tracks[curr] - difference;
        while (lopos >= 0){
            if (marks[lopos] == -1){
                possible = 0;
                break;
            }
            newBitmask = newBitmask & (1023 - (1 << marks[lopos]));
            lopos -= difference;
        }

        // Still possible?
        if (possible == 0) continue;

        // Look above
        int hipos = tracks[i] + difference;
        while (hipos < m){
            if (marks[hipos] == -1){
                possible = 0;
                break;
            }
            newBitmask = newBitmask & (1023 - (1 << marks[hipos]));
            hipos += difference;
        }

        // Still possible?
        if (possible == 0) continue;

        // OK it is possible, do DP.
        int nextIteration = dp(newBitmask) + 1;
        best = MIN(best, nextIteration);
    }

    // Memoize and return
    memo[bitmask] = best;
    return best; 
}

void solve(int m){
    scanf("%d", &n);

    // Calloc all my DSes
    tracks = calloc(sizeof(int), n+1);
    marks = calloc(sizeof(int), m);
    memo = calloc(sizeof(int), 1<<n);

    for (int i = 0; i < m; ++i){
        marks[i] = -1;
    }

    // Scan in the marks on the ground
    for (int i = 0; i < n; ++i){
        scanf("%d", &tracks[i]);
    }

    // They didn't guarantee the input will be sorted...
    qsort(tracks, n, sizeof(int), cmpfunc);

    for (int i = 0; i < n; ++i){
        marks[tracks[i]] = i;
    }

    // OK now we need to do dp
    printf("%d\n", dp((1<<n) - 1));

    // Don't forget to free dobbys
    free(tracks);
    free(marks);
    free(memo);
}

int main(){
    // Scan until EOF
    while (scanf("%d", &m) != EOF){
        solve(m);
    }

    return 0;
}

