#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int height;
    int diameter;
    int width;
} Doll;

Doll doll(int height, int diameter, int width){
    Doll out = {height, diameter, width};
    return out;
}

int cmpfunc(const void* a, const void* b){
    Doll first = *(Doll*) a;
    Doll second = *(Doll*) b;
    if (first.height != second.height) return first.height - second.height;
    if (first.diameter != second.diameter) return first.diameter - second.diameter;
    return second.width - first.width;
}

Doll dolls[405];

// Ghetto stack
int output[205];
int outputHead;
int AsDolls[405];

void push(int x){
    output[outputHead] = x;
    outputHead++;
}


// I don't want to reset the memo table
int memo[405][405][205][5]; // Set the bit if it is impossible
int n;
int t = 0;

// Returns 1 if doll at index x can fit inside doll at index y
int within(int x, int y){
    Doll first = dolls[x];
    Doll second = dolls[y];

    if (second.height - 2*second.width < first.height) return 0;
    if (second.diameter - 2*second.width < first.diameter) return 0;
    return 1;
}

// Return 1 if we have a solution path
int dp(int lastDollA, int lastDollB, int numDollsA, int numDollsB){
    // Have we reached the end of the dp?
    if (numDollsA == n && numDollsB == n) return 1;

    // Have been been here and realised its impossible?
    if (memo[lastDollA][lastDollB][numDollsA][t]) return 0;

    // Have we selected too many dolls?
    if (numDollsA > n || numDollsB > n) return 0;

    // Next doll is 1 + the number of dolls we have already chosen
    int nextDoll = numDollsA + numDollsB + 1;

    // Right, suppose the next doll is A's:
    if (within(lastDollA, nextDoll)){
        // Does this give a solution path?
        if (dp(nextDoll, lastDollB, numDollsA + 1, numDollsB)){

            // Push the doll into the correct answer array
            push(nextDoll);
            return 1;
        }
    }
    // It could also be B's
    if (within(lastDollB, nextDoll)){
        // Does this give a solution path?
        if (dp(lastDollA, nextDoll, numDollsA, numDollsB + 1)){

            // Here, we don't push because output array stores A's doll values
            return 1;
        }
    }

    // Nope, this route is a failure since we did not return success.
    // Memoize it for future generations.

    // Technically I can calculate the number of dollsB has:
    // It is given by the current doll (which is the max of lastDollA, and
    // lastDollB) subtract the number of dollsA has
    memo[lastDollA][lastDollB][numDollsA][t] = 1;
    return 0;
}

int solve(){
    // Scan in input
    for (int i = 0; i < 2*n; ++i){
        int height, diameter, width;
        scanf("%d %d %d", &height, &diameter, &width);
        dolls[i] = doll(height, diameter, width);
    }

    // Push a sentinel smol doll
    dolls[2*n] = doll(0, 0, 0);

    // Quicksort the dolls in accordance to height and width
    // This is in ascending order, with a sentinel 0 doll
    qsort(dolls, 2*n + 1, sizeof(Doll), cmpfunc);

    // Reset the output array
    outputHead = 0;
    dp(0, 0, 0, 0); 

    // Print out the dolls:
    // Reset the output array.
    for (int i = 1; i <= 2*n; ++i){
        AsDolls[i] = 0;
    }

    for (int i = 0; i < n; ++i){
        AsDolls[output[i]]++;
    }

    // Print out A's Dolls
    for (int i = 2*n; i > 0; --i){
        if (AsDolls[i] == 0){
            printf("%d %d %d\n", dolls[i].height, dolls[i].diameter, dolls[i].width);
        }
    }

    printf("-\n");

    // And then B's dolls
    for (int i = 2*n; i > 0; --i){
        if (AsDolls[i]){
            printf("%d %d %d\n", dolls[i].height, dolls[i].diameter, dolls[i].width);
        }
    }
}

int main(){
    scanf("%d", &n);

    while (n){
        solve();
        t++;
        printf("\n"); 
        scanf("%d", &n);
    }

    return 0;
}

