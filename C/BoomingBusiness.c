#include<stdio.h>

#define MOD 1000000007

long long dpTable[305][305];

long long memo(int height, int weight){

    // If we have memoized, return
    if (dpTable[height][weight] != -1) return dpTable[height][weight]; 

    // If not, break off the left subbranch and see
    long long out = 0;
    for (int newWeight = 0; newWeight < weight; ++newWeight){
        out += memo(height-1, newWeight) * memo(height, weight - 1 - newWeight);
        out %= MOD;
    }
    
    dpTable[height][weight] = out;
    return out;

}

void setting(){
    for (int i = 0; i < 305; ++i){
        for (int j = 0; j < 305; ++j){
            dpTable[i][j] = -1;
        }

        // 2 Base cases:
        // If height == 0 then 1 way
        // If weight == 0 then no way.
        dpTable[i][0] = 1L;
        dpTable[0][i] = 0;
    }
}


// This is the bottom up solution
/*
void solve(int height, int weight){
    // If height is 0, then there is one way
    // But if weight is 0, then there is no way
    for (int i = 0; i < 305; ++i){
        dpTable[i][0] = 1;
        dpTable[0][i] = 0;
    }

    // For each possible combi of height and weight
    for (int currWeight = 1; currWeight < 305; ++currWeight){
        for (int currHeight = 1; currHeight < 305; ++currHeight){
            long long out = 0;

            // Break off all possible left subtrees, and multiply
            for (int newWeight = 0; newWeight < currWeight; ++newWeight){
                out = (out + dpTable[currHeight-1][newWeight] * dpTable[currHeight][currWeight - 1 -  newWeight]) % MOD;
            }

            dpTable[currHeight][currWeight] = out;
        }
    }
}
*/

int main(){
    // Scan in input
    int w, h;
    scanf("%d %d", &h, &w);

    // Check if height = 1, if is it, only when w = 1 can there be a tree
    if (h == 1){
        printf("%d\n", (w == 1) ? 1 : 0);
        return 0;
    }

    // Remove 1 from the weight because that's the base branch.
    w--;

    // Set up and run the memotable
    setting(h, w);
    printf("%lld\n", (memo(h, w) - memo(h-1, w) + MOD) % MOD);

    return 0;
}
