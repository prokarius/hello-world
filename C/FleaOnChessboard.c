#include<stdio.h>

// Returns the parity of the square at (x, y)
long long parity(long long x, long long y, long long s){
    long long numRow = x / s;
    long long numCol = y / s;
    return (numRow + numCol) % 2;
}

int main(){
    // Scan in input
    // LONG LONG DAMNIT
    long long s, x, y, dx, dy;
    scanf("%lld %lld %lld %lld %lld", &s, &x, &y, &dx, &dy);

    // Small hack to break only when all of them are true
    while (s || x || y || dx || dy){

        // Originally I was thinking we can solve some diophantine equation
        // (a * dx + x)/s + (b * dy + y)/s = (2k + 1)
        // So this gives the parity of the square

        // But ehh, what's the point. We can just simulate 1mil steps no?
        int numJumps = 0;
        while (numJumps < 2*s + 1){
            // 2 conditions to break:
            // 1) We must be within a square
            // 2) The square is of the correct parity
            if (x % s != 0 && y % s != 0 && parity(x, y, s)) break;
            x += dx;
            y += dy;
            ++numJumps;
        }

        // Did we die?
        if (numJumps == 2*s + 1){
            printf("The flea cannot escape from black squares.\n");
        }
        else {
            printf("After %d jumps the flea lands at (%lld, %lld).\n", numJumps ,x,y);
        }

        scanf("%lld %lld %lld %lld %lld", &s, &x, &y, &dx, &dy);
    }

    return 0;
}

