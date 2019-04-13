#include<stdio.h>

int films[1000005][2];

int main(){
    // Scan in input
    int a, b;

    scanf("%d", &a);
    for (int i = 0; i < a; ++i){
        int likedFilm;
        scanf("%d", &likedFilm);
        films[likedFilm][0] = 1;
    }

    scanf("%d", &b);
    for (int i = 0; i < b; ++i){
        int likedFilm;
        scanf("%d", &likedFilm);
        films[likedFilm][1] = 1;
    }

    // Greedily sweep through all the days.
    // Always choose to watch the current film if possible.
    // Set a flag for the other person if he doesn't like it.
    int curr = 0;
    int cannota = 0;
    int cannotb = 0;
    for (int i = 0; i < 1000002; ++i){
        if (films[i][0] && !cannota){
            curr++;
            cannotb = 0;
            if (!films[i][1]) cannota = 1;
            else cannota = 0;
        }
        else if (films[i][1] && !cannotb){
            curr++;
            cannota = 0;
            if (!films[i][0]) cannotb = 1;
            else cannotb = 0;
        }
    }

    // Print the answer
    printf("%d\n", curr);

    return 0;
}
