#include<stdio.h>

int gnomes[100005];
int current[100005];

int main(){
    // Scan in input
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i){
        scanf("%d", &current[i]);
        gnomes[current[i]] = 1;
    }

    // Add a sentinel value
    current[m] = 1<<30;

    int counter = 0;
    for (int i = 1; i <= n; ++i){
        // Is the current gnome smaller than i?
        while (current[counter] <= i){
            printf("%d\n", current[counter]);
            counter++;
        }

        // Then if we have not seen the gnome before, print it
        if (gnomes[i] != 1){
            printf("%d\n", i);
        }
    }

    return 0;
}

