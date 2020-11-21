#include<stdio.h>

int array[1<<14];

int majority(int start, int end){
    int count = 0;
    int element = -1;

    for (int i = start; i <= end; ++i){
        if (count == 0){
            element = array[i];
            ++count;
        }
        else if (element == array[i]) count++;
        else count--;
    }

    // One more loop through to count the number of elements
    count = 0;
    for (int i = start; i <= end; ++i){
        if (array[i] == element) ++count;
    }

    return count > ((end - start + 1) / 2);
}

int main(){
    // Scan in input
    int n, q;
    scanf("%d %d", &n, &q);

    // Convert all the floats to 
    for (int i = 1; i <= n; ++i){
        float x;
        scanf("%f", &x);
        array[i] = (int) (x * 1000000);
    }

    for (int i = 0; i < q; ++i){
        int start, end;
        scanf("%d %d", &start, &end);

        printf(majority(start, end)?"":"un");
        printf("usable\n");
    }

    return 0;
}

