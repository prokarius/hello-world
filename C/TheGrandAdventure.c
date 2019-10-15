#include<stdio.h>
#include<string.h>

// Backpack methods
int backPackHead = 0;
char backPack[128];

void resetBackPack(){
    backPackHead = 0;
}

// Push a new item into the stack
void push(char c){
    backPack[backPackHead] = c;
    backPackHead++;
}

// Pop and return the highest item in the stack
char pop(){
    backPackHead--;
    // If backPack is empty, return special value
    if (backPackHead < 0){
        return 0;
    }
    return backPack[backPackHead];
}

int size(){
    return backPackHead;
}

char adventure[128];

void solve(){
    scanf("%s", adventure);
    int length = strlen(adventure);
    
    // Reset the backpack always before running the code
    resetBackPack();

    // For each character, do the actions
    for (int i = 0; i < length; ++i){
        char prev;
        switch (adventure[i]){
            case '$':
                push('$');
                break;
            case '|':
                push('|');
                break;
            case '*':
                push('*');
                break;
            case 't':;
                prev = pop();
                if (prev != '|'){
                    printf("NO\n");
                    return;
                }
                break;
            case 'j':;
                prev = pop();
                if (prev != '*'){
                    printf("NO\n");
                    return;
                }
                break;
            case 'b':;
                prev = pop();
                if (prev != '$'){
                    printf("NO\n");
                    return;
                }
                break;
            default:
                break;
        }
    }

    // The adventure ends, check the size of his bag
    if (size() != 0){
        printf("NO\n");
    }
    else{
        printf("YES\n");
    }
}

int main(){
    // Scan in input
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}

