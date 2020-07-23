#include<stdio.h>
#include<string.h>

int charset[256]; // ghettoHashSet for characters
int unique[16]; // List of unique letters
int numChars = 0; // number of unique characters in the puzzle
char string[16]; // To scan in the string
int blacklist[256]; // Blacklist the starting letters of each word

// lhs[x] captures the contribution of x as a digit.
int lhs[256]; // Addands
int rhs[256]; // Summand

int used[16]; // For recursion
int ways = 0;

// For each potential way we find, do ways++
// curr stores the index of which unique letter we are looking at
void bruteforce(int curr, int LHS, int RHS){
    // Basecase, if we processed all the unique letters already
    // Check if LHS = RHS
    if (curr == numChars){
        if (LHS == RHS) ways++;
        return;
    }

    // Bruteforce all possible value for the current letter
    int currLetter = (int) unique[curr];
    for (int i = 0; i < 10; ++i){

        // Prune: If we have assigned a number before, continue
        if (used[i]) continue;
        // Prune: If the number we are assigning is 0, but the letter is
        // blacklisted, continue
        if (i == 0 && blacklist[currLetter]) continue;

        // Recurse!
        used[i] = 1;
        int newLHS = LHS + lhs[currLetter] * i;
        int newRHS = RHS + rhs[currLetter] * i;
        bruteforce(curr+1, newLHS, newRHS);
        used[i] = 0;
    }
}

int main(){
    // Scan in input
    int n;
    scanf("%d ", &n);
    for (int i = 0; i < n-1; ++i){
        scanf(" %s", string);

        // Find out which letters are used, and how much they contribute
        int power = 1;
        for (int j = strlen(string)-1; j >= 0; --j){
            int charVal = (int) string[j];
            if (used[charVal] == 0){
                used[charVal] = 1;
                unique[numChars++] = string[j];
            }

            lhs[charVal] += power;
            power *= 10;
        }

        // Blacklist the first letter
        blacklist[(int) string[0]] = 1; 
    }

    // Process rhs
    scanf(" %s", string);

    // Find out which letters are used, and how much they contribute
    int power = 1;
    for (int j = strlen(string)-1; j >= 0; --j){
        int charVal = (int) string[j];
        if (used[charVal] == 0){
            used[charVal] = 1;
            unique[numChars++] = string[j];
        }

        rhs[charVal] += power;
        power *= 10;
    }

    // Blacklist the first letter
    blacklist[(int) string[0]] = 1; 

    // Bruteforce all combinations using recursion:
    bruteforce(0, 0, 0);

    printf("%d\n", ways);
    return 0;
}

