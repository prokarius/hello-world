#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

#define MIN(x, y) (((x) < (y))?(x):(y))

char* wordsA[16];
char* wordsB[16];
int lengthsA[16]; // Precache the lengths maybe?
int lengthsB[16];
char* best;
int bestlen;
int used[16];

void recurse(char* strA, char* strB, int lenA, int lenB, int curr, int n){
    if (curr == n) return;
    
    // Try each possible word
    for (int i = 0; i < n; ++i){
        if (used[i]) continue;
        used[i] = 1;

        int possible = 1;

        // Only if we have not seen the word before
        if (lenA == 0){
            if (wordsA[i][0] != wordsB[i][0]) possible = 0;
        }
        else if (lenA > lenB){
            if (wordsB[i][0] != strA[lenB]) possible = 0;
        }
        else { // lenA < lenB
            if (wordsA[i][0] != strB[lenA]) possible = 0;
        }

        // Prune: If the best is shorter than us, give up
        if (MIN(lengthsA[i] + lenA, lengthsB[i] + lenB) > bestlen) possible = 0;

        // Only recurse if it is possible
        if (possible){
            // Optimize: Roll my own strcat
            // strcat(strA, wordsA[i]);
            // strcat(strB, wordsB[i]);
            for (int j = 0; j < lengthsA[i]; ++j){
                strA[lenA + j] = wordsA[i][j];
            }
            strA[lenA + lengthsA[i]] = 0;
            for (int j = 0; j < lengthsB[i]; ++j){
                strB[lenB + j] = wordsB[i][j];
            }
            strB[lenB + lengthsB[i]] = 0;

            // Optimize: Roll my own strcmp
            // Check if any letters are off
            int currlenA = lengthsA[i] + lenA;
            int currlenB = lengthsB[i] + lenB;
            
            int start = MIN(lenA, lenB);
            int end = MIN(currlenA, currlenB);

            for (int j = start; j < end; ++j){
                if (strA[j] != strB[j]){
                    possible = 0;
                    break;
                }
            }

            // If it is possible that the words are still the same?
            if (possible){
                // Are they of the same length?
                if (currlenA == currlenB){
                    // And only if it beats best:
                    if (currlenA < bestlen ||
                        ((currlenA == bestlen) && (strcmp(strA, best) < 0))){
                        char* currBest = (char*) malloc(2048 * sizeof(char));
                        strcpy(currBest, strA);
                        best = currBest;
                        bestlen = currlenA;
                    }
                }
                else {
                    recurse(strA, strB, currlenA, currlenB, curr+1, n);
                }
            }
        }

        // Remove the additions by null terminating the strings
        strA[lenA] = 0;
        strB[lenB] = 0;
        used[i] = 0;
    }
}

void solve(int n, int numTest){
    // Scan in input
    for (int i = 0; i < n; ++i){
        char* strA = (char*) malloc(128 * sizeof(char));
        char* strB = (char*) malloc(128 * sizeof(char));
        scanf("%s %s", strA, strB);
        wordsA[i] = strA;
        wordsB[i] = strB;
        lengthsA[i] = strlen(strA);
        lengthsB[i] = strlen(strB);
    }

    // Now do recursion on the outputs
    char* input = (char*) malloc(2048 * sizeof(char));
    char* output = (char*) malloc(2048 * sizeof(char));

    bestlen = 9999;
    best = "";
    recurse(input, output, 0, 0, 0, n);

    if (bestlen == 9999){
        best = "IMPOSSIBLE";
    }

    printf("Case %d: %s\n", numTest, best);
}

int main(){
    int count = 1;
    int n;
    while(scanf("%d", &n) != EOF){
        solve(n, count);
        ++count;
    }
    return 0;
}

