#include<stdio.h>
#include<string.h>

char string[2000005];

void solve(){
    int length = strlen(string);

    // Just test everything I guess...?
    for (int potential = 1; potential <= length/2; ++potential){
        if (length % potential != 0) continue;

        int possible = 1;
        for (int i = potential; i < length; i++){
            if (string[i] != string[i-potential]){
                possible = 0;
                break;
            }
        }

        if (possible){
            printf("%d\n", length / potential);
            return;
        }
    }

    // We can't find any repeated cycles
    printf("1\n");
}

int main(){
    // Scan in input:
    scanf("%s", string);

    while(string[0] != '.'){
        solve();
        scanf("%s", string);
    }

    return 0;
}
