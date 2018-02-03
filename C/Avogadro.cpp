#include<cstdio>
#include<set>

// Initialise all the variables
bool deleted[100005]; // Keep track of all the deleted columns
int arr [3][100005]; // Is the input table
int instance[3][100005]; // Stores #instances in each row
std::set<int> vecset[100005]; // Stores col number of each number
int toDelete[1000005]; // Store cols we want to delete in a ghettoStack
int stackHead = 0;
int size = 0; // output

void push(int n){
    toDelete[stackHead++] = n;
}

int pop(){
    return toDelete[--stackHead];
}


int main(){
    int n, i, j, ph;
    scanf("%d", &n);

    // Scan in the input
    for (i=0; i<3; ++i){
       for (j=0; j<n; ++j){
           scanf("%d", &ph);
           arr[i][j] = ph;
           vecset[ph].insert(j);
           ++instance[i][ph];
        }
        // Push the numbers which don't appear in any row.
        for (j=1; j<=n; ++j){
            if (instance[i][j] == 0) push(j);
        }
    }

    // while we have numbers to delete, delete numbers
    while (stackHead > 0){
        // For each column Q which N appears in:
        int N = pop();
        for (auto Q : vecset[N]){
            // If not already in output, add them in
            if (!deleted[Q]){
                ++size;
                deleted[Q] = true;
                // For the numbers M in the three rows of column Q:
                // reduce their instances by 1 and check if 0
                for (i=0; i<3; ++i){
                    int M = arr[i][Q];
                    --instance[i][M];
                    if (instance[i][M] == 0) push(M);
                }
            }
        }
    }

    printf("%d\n", size);
    return 0;
}
