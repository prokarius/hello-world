#include<stdio.h>

int ways[1100005];

int main(){
    // Suppose you want to by n houses. How much do they cost?
    // There are 2 cases to consider. We count all the cases from there
    
    // Case 1: n is odd
    // Then you will need n*k amount of money, where k starts from (n+3)/2
    // E.g. for 5 houses, you need 4*5 (2,3,4,5,6) | 5*5 (3,4,5,6,7) etc.
    // This is because we center the middle element and wrap the other elements around
    for (int i = 3; i*i < 2000005; i+=2){
        for (int k = (i+3)/2; k*i < 1000005; ++k){
            ++ways[k*i];
        }
    }
    
    // Case 2: n is even
    // Then you will need (n*k + n/2) money
    // Think of the sum as a pyramid:
    //
    // ##@      (n*k) refers to the o's. If we get rid of them, then we can
    // ##@@     Put the @'s next to the x's and form a rectangle of height
    // ##oxx    n/2 and length n
    // ##oxxx   Then, the #'s (which is the increasing k) tells us where to start
    // 
    for (int i = 2; i*i < 2000005; i+=2){
        for (int k = i/2+1; k*i < 1000005; ++k){
            ++ways[i*k + i/2];
        }
    }

    // Since there is no house 1.
    ways[1] = -1;

    // Scan in input and just print
    int query;
    scanf("%d", &query);
    while (query){
        printf("%d\n", ways[query]+1);
        scanf("%d", &query);
    }

    return 0;
}
