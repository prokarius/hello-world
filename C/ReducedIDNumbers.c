#include<stdio.h>

int numbers[305];
int modulo[1000005];

int main(){
    int n;

    // Scan in input
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &numbers[i]);
    }

    // Just try all possible mods lol
    for (int i = n; i < 1000005; ++i){
        for (int j = 0; j < i; ++j){
            modulo[j] = 0;
        }

        int flag = 0;

        for (int j = 0; j < n; ++j){
            if (modulo[numbers[j] % i]){
                flag++;
                break;
            }
            modulo[numbers[j] % i] = 1;
        }

        if (flag) continue;

        printf("%d\n", i);
        break;
    }

    return 0;
}
