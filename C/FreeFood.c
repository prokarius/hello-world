#include<stdio.h>

int freefood[400];

int main(){
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        while (start <= end){
            freefood[start]++;
            start++;
        }
    }

    int output = 0;
    for (int i = 0; i <= 365; ++i){
        if (freefood[i]) output++;
    }

    printf("%d\n", output);

    return 0;
}

