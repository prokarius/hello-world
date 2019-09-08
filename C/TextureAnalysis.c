#include<stdio.h>
#include<string.h>

char str[1024];

void solve(int testcase){
    // Initialise variables
    int count = 0;
    int runlength = -1;

    for (int i = 1; i < strlen(str); ++i){

        // If we find *, check to see if we have anything banked
        if (str[i] == '*'){

            // If we have not banked anything before
            if (runlength == -1){
                runlength = count;
            }
            else if (runlength != count){
                printf("%d NOT EVEN\n", testcase);
                return;
            }
            count = 0;
        }

        // Else if we see a ., add 1 to count
        else {
            count++;
        }
    }
    printf("%d EVEN\n", testcase);
}

int main(){
    // Scan in input
    scanf("%s", str);
    int testcase = 0;

    while (strcmp(str, "END") != 0){
        testcase++;
        solve(testcase);
        scanf("%s", str);
    }

    return 0;
}

