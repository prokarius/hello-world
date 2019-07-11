#include<stdio.h>

char string[10005];
char decoded[10005];
char encoded[10005];

// Process the string and return the number of letters
int processString(char* string){
    int numChars = 0;

    for (int i = 0; string[i] != 0; ++i){

        // Ignore if it is a white space
        if (string[i] == ' ') continue;

        // Process if it is lowercase
        if (string[i] >= 'a'){
            decoded[numChars++] = string[i] - 32;
        }
        // Copy if it is uppercase
        else {
            decoded[numChars++] = string[i];
        }
    }

    // Return
    return numChars;
}

void solve(int n){
    // Scan in input
    // This glyph means scan a string until it reaches a newline character
    scanf(" %[^\n]", string);

    // Process the string to get the decoded message
    int numChars = processString(string);

    // Keep track of the current starting character
    // Nasty hack, set current index to be a huge number so it always triggers the
    // overflow of the currentIndex check
    int currStart = -1;
    int currIndex = 1 << 30;

    // Encode the message shittily
    for (int i = 0; i < numChars; ++i){
        if (currIndex >= numChars){
            ++currStart;
            currIndex = currStart;
        }
        encoded[currIndex] = decoded[i];
        currIndex += n;
    }

    // Put a null byte at the end so we can just print the string
    encoded[numChars] = 0;

    // Print that shit
    printf("%s\n", encoded);
}

int main(){
    int n;
    scanf("%d", &n);

    while (n != 0){
        solve(n);
        scanf("%d", &n);
    }

    return 0;
}

