#include<stdio.h>
#include<stdlib.h>

#define MIN(x,y) (x < y)?(x):(y)
#define MAX(x,y) (x > y)?(x):(y)

typedef struct {
    int x;
    int y;
} House;

House house (int x, int y){
    House output;
    output.x = x;
    output.y = y;
    return output;
}


// Compares the houses by y values
int cmpfuncy(const void* a, const void* b){
    House first = *(House*) a;
    House second = *(House*) b;

    return first.y - second.y;
}

// We also need one by x values
int cmpfuncx(const void* a, const void* b){
    House first = *(House*) a;
    House second = *(House*) b;

    return first.x - second.x;
}

House houses[128*128];
int streets[128];

int output[128];

int count[128][128];
int dp[128][128];
int from[128][128];

// Stores all the houses in a partition
House partitionHouses[128*128];

void solve(int numHouses){
    // Scan in input
    for (int i = 0; i < numHouses; ++i){
        int x, y;
        scanf("%d %d", &x, &y);

        // Swap x and y cuz streets and avenues
        // Also subtract 1 before no one has time for 1 based indexing
        houses[i] = house(y-1, x-1);
    }

    // Create a sentinel house. It will help with making the count table later.
    houses[numHouses] = house(10007,10007);

    // Sort the houses by their y values
    qsort(houses, numHouses + 1, sizeof(House), cmpfuncy);

    // Scan in the rows that have partitions
    int numStreets;
    scanf("%d", &numStreets);

    for (int i = 0; i < numStreets; ++i){
        int street;
        scanf("%d", &street);
        streets[i] = street-1;
    }

    // Initialize the helper counting array
    // count[x][y] stores the number of ridings with an opposing neighborhood
    // that we can get if we sliced between the range x and y
    for (int i = 0; i <= 100; ++i){
        for (int j = i; j <= 100; ++j){
            count[i][j] = 0;
        }
    }

    // Let us get all the houses in between the streets. Then sort by x coordinate.
    // Given 2 houses, anything that starts before the first house and ends after
    // the first would give a count.
    // Anything that starts between first and second that ends after the second
    // would also give a count.
    int currHouse = 0;
    for (int i = 1; i < numStreets; ++i){
        int numHousesInPartition = 1;
        while (houses[currHouse].y < streets[i]){
            partitionHouses[numHousesInPartition] = houses[currHouse];
            ++numHousesInPartition;
            ++currHouse;
        }

        // Add a sentinel
        partitionHouses[0] = house(-1, -1);
        qsort(partitionHouses, numHousesInPartition, sizeof(House), cmpfuncx);

        // Fill
        for (int k = 1; k < numHousesInPartition; ++k){
            int leftHouse = partitionHouses[k-1].x;
            int rightHouse = partitionHouses[k].x;

            // Also remember to fill from the right house to 100
            // But break if we have already done it
            for (int i = rightHouse; i > leftHouse; --i){
                for (int j = rightHouse+1; j <= 100; ++j){
                    count[i][j]++;
                }
            }
        }
    }

    // But remember that the diagonal should be 0
    for (int i = 0; i < 102; ++i){
        count[i][i] = 0;
    }

    // Alright, it's time to do some dp.
    // Scan in the number of partitions we need to make
    int numPartitions;
    scanf("%d", &numPartitions);

    // Reset the dp array
    // dp[x][y] stores the maximum number of regions with points given
    // x lines has been put down
    // The right most line put down is y
    for (int i = 0; i < numPartitions; ++i){
        for (int j = 0; j < 101; ++j){
            dp[i][j] = -9999999;
        }
    }
    dp[0][0] = 0;

    // For each time we get to choose a partition, we check where the best place to
    // put a new right partition is
    for (int partition = 1; partition < numPartitions; ++partition){
        for (int rightPartition = 100; rightPartition > 0; --rightPartition){
            for (int leftPartition = 0; leftPartition < rightPartition; ++leftPartition){
                dp[partition][rightPartition] = MAX(dp[partition][rightPartition],
                        dp[partition-1][leftPartition] + count[leftPartition][rightPartition]);
            }
        }
    }

    // It's time to print
    printf("%d", numPartitions);
    numPartitions--;
    int partitions = numPartitions;

    // Walk backwards through the dp array, and check to see which left / partition
    // caused the output
    // Standard DP practice
    int currentRight = 99;
    while (partitions != 0){
        int leftPartition = currentRight-1;
        while(leftPartition >= 0){
            if (dp[partitions][currentRight] == dp[partitions - 1][leftPartition] + count[leftPartition][currentRight]){

                // Set the new left and right partitions
                output[partitions] = currentRight+1;
                output[partitions-1] = leftPartition+1;
                currentRight = leftPartition;
                --partitions;
                break;
            }
            leftPartition--;
        }
    }

    // Print the cached values, since it is backwards
    for (int i = 0; i <= numPartitions; ++i){
        printf(" %d", output[i]);
    }

    // Finish off with the newline.
    printf("\n");
 }

int main() {
    // Scan in input
    int n;
    scanf("%d", &n);

    while (n != -1){
        solve(n);
        scanf("%d", &n);
    }

    return 0;
}

