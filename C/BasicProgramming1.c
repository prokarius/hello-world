#include<stdio.h>
#include<stdlib.h>

int cmpfunc(const void* a, const void* b){
    return *(int*)a - *(int*) b;
}

int array[200005];
int visited[200005];

void cyclic(int n){
    int curr = 0;
    
    while(1){
        curr = array[curr];
        if (curr >= n){
            printf("Out\n");
            return;
        }

        if (curr == n-1){
            printf("Done\n");
            return;
        }

        if (visited[curr]){
            printf("Cyclic\n");
            return;
        }

        visited[curr] = 1;
    }
}

int main(){
    // Scan in input
    int n, t;
    scanf("%d %d", &n, &t);

    for (int i = 0; i < n; ++i){
        scanf("%d", &array[i]);
    }

    long long sum = 0;

    switch(t){
        case(1):
            printf("7\n");
            break;

        case(2):
            if (array[0] == array[1]) printf("Equal\n");
            else printf(array[0] > array[1] ? "Bigger\n" : "Smaller\n");
            break;

        case(3):
            // Sigh this is overkill...
            qsort(array, 3, sizeof(int), cmpfunc);
            printf("%d\n", array[1]);
            break;

        case(4):
            for (int i = 0; i < n; ++i) sum += array[i];
            printf("%lld\n", sum);
            break;

        case(5):
            for (int i = 0; i < n; ++i){
                if (array[i] % 2 == 0){
                    sum += array[i];
                }
            }
            printf("%lld\n", sum);
            break;

        case(6):
            for (int i = 0; i < n; ++i){
                printf("%c", 97 + (array[i] % 26));
            }
            printf("\n");
            break;

        case(7):
            cyclic(n);
            break;
    }

    return 0;
}

