#include<stdio.h>
#include<string.h>

char text[1<<21];
char print[1<<21];
int aux[1<<21]; // Stores the LPS position i.e. LPS[aux2[writeHead]]
int aux2[1<<21]; // Stores the value of curr
char bug[1024];
int LPS[1024];

void KMP(int n){
    // Scan in input
    scanf("%[^\n]", bug);
    getchar();

    // Construct KMP array
    int prefix = 0;
    int i = 1;
    int bugLen = strlen(bug);

    while (i < bugLen){
        if (bug[prefix] == bug[i]){
            prefix++;
            LPS[i++] = prefix;
        }
        else if (prefix){
            prefix = LPS[prefix-1];
        }
        else{
            LPS[i] = 0;
            i++;
        }
    }

    // Scan in each line and do KMP matching
    for (int i = 0; i < n; ++i){
        // Duct tape: If we don't scan anything, set text to be null string
        text[0] = '\0';

        scanf("%[^\n]", text);
        getchar();

        int textLen = strlen(text); 
        int target = 0;
        int curr = 0;
        int writeHead = 0;

        // Do KMP matching
        while (curr < textLen){
            if (text[curr] == bug[target]){
                aux2[writeHead] = curr;
                print[writeHead++] = text[curr];
                target++;

                // Set the aux array's contents to store the KMP matching info
                aux[curr] = target;
                curr++;

                // If we have matched, then delete the bug by moving writeHead back
                if (target == bugLen){
                    writeHead -= bugLen;
                    if (writeHead == 0) target = 0;
                    else target = aux[aux2[writeHead-1]];
                }
            }
            else if (target){
                target = LPS[target-1];
            }
            else {
                aux2[writeHead] = curr;
                print[writeHead++] = text[curr];
                aux[curr] = 0;

                curr++;
            }
        }

        // Put the null byte at the end of the string
        print[writeHead] = '\0';
        printf("%s\n", print);
    }
}

int main(){
    int n;

    // Do KMP
    while(scanf("%d ", &n) != EOF){
        KMP(n);
    }

    return 0;
}

