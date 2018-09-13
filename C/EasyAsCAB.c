#include<stdio.h>
#include<stdlib.h>

// Since it's only 26 alphabets maximum, we can live with an adjMatrix
int adjMatrix[26][26];
int visited[26];
int recursionStack[26];
int loopyBoiFlag = 0;
char topoString[27];
int topoStringHead = 0;
int n, numChars;

void toposort (int x){
    visited[x] = 1;
    recursionStack[x] = 1;
    for (int i = 0; i < numChars; ++i){
        if (adjMatrix[x][i]){
            // Check to see if we we have reached this vertex before
            if (1-visited[i]) toposort(i);
            else if (recursionStack[i]) loopyBoiFlag = 1;
        }
    }
    recursionStack[x] = 0;
    topoString[topoStringHead++] = x;
}

int main(){
    char maxChar;
    char* strings[1003];
    scanf("%c %d", &maxChar, &n);
    numChars = maxChar - 'a' + 1;

    // Scan in all the strings
    for (int i = 0; i < n; ++i){
        strings[i] = malloc(1005 * sizeof(char));
        scanf("%s", strings[i]);
    }

    // Now, we populate the dependency list
    for (int i = 0; i < n-1; ++i){
        int index = 0;
        while (1){
            char first = strings[i][index];
            char second = strings[i+1][index];

            // If we encounter a '\0' on second, that's wrong!
            // "shoehorn" comes after "shoe" for example
            if (second == '\0'){
                printf("IMPOSSIBLE\n");
                return 0;
            }

            // If the first guy is the end of the string that ain't tell us shit.
            if (first == '\0') break;

            // Else, we set an edge whenever the characters are different
            // Also, terminate there and then.
            if (first != second){
                adjMatrix[first - 'a'][second - 'a'] = 1;
                break;
            }
            index++;
        }
    }

    // It's toposort time.
    for (int i = 0; i < numChars; ++i){
        if (1 - visited[i]) toposort(i);
    }

    // If we have trigged the loopyBoiFlag, it's Impossible
    if (loopyBoiFlag){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    // First we check for uniqueness
    for (int i = 0; i < numChars - 1; ++i){
        if (1-adjMatrix[topoString[i+1]][topoString[i]]){
            printf("AMBIGUOUS\n");
            return 0;
        }
    }

    // Reverse the string and print it
    for (int i = numChars-1; i >= 0; --i){
        printf("%c", topoString[i] + 'a');
    }
    printf("\n");
    return 0;
}
