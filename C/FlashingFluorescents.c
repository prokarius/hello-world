#include<stdio.h>

// seen array, for dp.
int seen[1<<16];

// This will be my ghettoStack to store all the points to be considered
int ghettoStack[1<<16];
int ghettoStackHead = 0;

void push(int x){
    ghettoStack[ghettoStackHead++] = x;
}

int main(){
    char inputstr[20];
    int length = 0;

    // Scan in the string
    scanf("%s", inputstr);

    // We want to see what the bitmasked value of the input is
    int value = 0;
    for (int i = 0; ; ++i){
        if (inputstr[i] == '\0'){
            break;
        }
        value = (value << 1) + inputstr[i] - '0';
        ++length;
    }

    // Set up the target value and check if we have won
    int target = (1 << length) - 1;
    if (target == value){
        printf("0\n");
        return 0;
    }

    // Now we mark this value as seen before in our dp table
    // And push it into our ghettostack for processing
    seen[value] = 0;
    push(value);

    // Anyways, so we start counting upwards from day 1:
    int out = 0;
    while (1){
        out++;
        int numEntries = ghettoStackHead;

        // For each of the entries in our ghettoStack
        // We try flicking all possible switches.
        for (int i = 0; i < numEntries; ++i){
            int currvalue = ghettoStack[i];
            int xormask = (1 << out) - 1;

            for (int j = 0; j <= length; ++j){
                int currxormask;
                // This bit is if we flick the switch correctly
                if (j <= length - out){
                    currxormask = xormask << j;
                }

                // Now, it can also be the case where the light has reached
                // the end. We need to account for that as well
                else {
                    currxormask = xormask >> (j + out - length);
                }
                int newvalue = currvalue ^ currxormask;

                // If the value we get is everything on, we win!
                if (newvalue == target){
                    printf("%d\n", out);
                    return 0;
                }

                // If not, if we haven't seen it before, make it seen
                // Also, add it to our list of states to process
                if (seen[newvalue] == 0){
                    seen[newvalue] = 1;
                    push(newvalue);
                }
            }
        }
    }
    return 0;
}
