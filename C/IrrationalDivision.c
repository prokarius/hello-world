#include<stdio.h>

int main(){
    // Scan in input
    int p, q;
    scanf("%d %d", &p, &q);

    // If the side length is odd, we can always get 1 point more than the other
    if (p&1 && q&1){
        printf("1\n");
        return 0;
    }

    // If our side length is even (i.e. sister will get equal numbers of dark and
    // white chocolate), then we can always force a draw by ensuring sister's side
    // is always an even number of square
    if (~p & 1){
        printf("0\n");
        return 0;
    }

    // Here, our side length is odd, but sister's side length is even.
    // If we have more squares than sister, then we can break off to form a square
    // (with odd sides) This will net us 1 point.
    // Now it's sister's turn, and no matter how many she breaks off, we just match
    // it. Eventually she'll need to take the top right corner square (which is -1)
    if (q > p){
        printf("2\n");
        return 0;
    }

    // And if we cannot play this strategy, just force a draw by taking everything
    printf("0\n");
    return 0;
}
