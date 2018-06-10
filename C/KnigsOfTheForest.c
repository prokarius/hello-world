#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int year;
    int power;
} Knig;

int cmpfunc(const void *a, const void *b){
    return (*(Knig*)a).year - (*(Knig*)b).year;
}

int main(){
    // Scan in Input
    int n, k;
    Knig knig[200005];
    scanf("%d %d", &k, &n);

    // Scan in the array of Knigs
    for (int i = 0; i < n+k-1; ++i){
        scanf ("%d %d", &knig[i].year, &knig[i].power);
    }

    // Keep the year Karl has entered
    int karlYear = knig[0].year;
    int karlPower = knig[0].power;

    // Sort the list of Knigs
    qsort(knig, n+k-1, sizeof(Knig), cmpfunc);

    // Count the number of Knigs less powerful than Karl
    int count = 0;
    for (int i = 0; i < n+k-1; ++i){
        if (knig[i].power <= karlPower){
            ++count;

            // If there are more than k-1 Knigs less powerful than Karl
            // Print his year, or the current year, whichever is higher.
            if (count >= k){
                printf("%d\n", karlYear > knig[i].year ? karlYear : knig[i].year);
                return 0;
            }
        }
    }

    // Else the thing is unknown
    printf ("unknown\n");
    return 0;
}
