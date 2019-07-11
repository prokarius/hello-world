#include<stdio.h>
#include<string.h>

long long maximum[128][128];
long long minimum[128][128];

char operations[128];
long long numbers[128];

long long MIN(long long x, long long y){
    return (x < y)?(x):(y);
}

long long MAX(long long x, long long y){
    return (x > y)?(x):(y);
}

// Parses the expression and returns the number of numbers parsed
int parseString(char* string){
    int index = 0;
    int currNum = 0;

    // While we have not reached the null byte
    for (int i = 0; string[i] != 0; ++i){

        // If we do not hit an operator, we parse the number
        if (string[i] != '+' && string[i] != '*'){
            currNum = currNum * 10 + string[i] - '0';
            continue;
        }

        // Else add the operator to the list of operators
        // And add the number we have parsed to the running list
        operations[index] = string[i];
        numbers[index] = currNum;
        ++index;
        currNum = 0;
    }

    // The last number has not been saved yet!
    numbers[index] = currNum;
    ++index;

    return index;
}

int main(){
    // Scan in input
    char string[1024];
    scanf(" %s", string);
    while (strcmp(string, "END") != 0){

        // Parse the string to get the list of operators and numbers
        int n = parseString(string);

        // We will need to do DP here
        // Reset the DP array
        for (int i = 0; i < n-1; ++i){
            for (int j = i+1; j < n; ++j){
                maximum[i][j] = -1;
                minimum[i][j] = 1LL << 62;
            }
        }

        // Also, at best, the max and min of each number is the number itself
        for (int i = 0; i < n; ++i){
            minimum[i][i] = numbers[i];
            maximum[i][i] = numbers[i];
        }

        // For each possible span of equation sizes
        for (int eqnSize = 1; eqnSize < n; ++eqnSize){

            // For each possible starting point:
            for (int startIndex = 0; startIndex < n - eqnSize; ++startIndex){

                // And for each possible operator we can split the chunk
                for (int breakPoint = startIndex; breakPoint < startIndex + eqnSize; ++breakPoint){

                    // Run the calculations
                    if (operations[breakPoint] == '+'){
                        minimum[startIndex][startIndex + eqnSize] = MIN(minimum[startIndex][startIndex + eqnSize],
                                minimum[startIndex][breakPoint] + minimum[breakPoint+1][startIndex + eqnSize]);
                        maximum[startIndex][startIndex + eqnSize] = MAX(maximum[startIndex][startIndex + eqnSize],
                                maximum[startIndex][breakPoint] + maximum[breakPoint+1][startIndex + eqnSize]);
                    }
                    else { // operations[breakPoint] == '*'
                        minimum[startIndex][startIndex + eqnSize] = MIN(minimum[startIndex][startIndex + eqnSize],
                                minimum[startIndex][breakPoint] * minimum[breakPoint+1][startIndex + eqnSize]);
                        maximum[startIndex][startIndex + eqnSize] = MAX(maximum[startIndex][startIndex + eqnSize],
                                maximum[startIndex][breakPoint] * maximum[breakPoint+1][startIndex + eqnSize]);
                    }
                }
            }
        }

        // Print that shit
        printf("%lld %lld\n", minimum[0][n-1], maximum[0][n-1]);

        scanf(" %s", string);
    }
}

