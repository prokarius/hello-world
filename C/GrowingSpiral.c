#include<stdio.h>

int main(){
    int testcases;
    scanf ("%d", &testcases);
    while (testcases--){
        int num, x, y;
        scanf("%d %d %d", &num, &x, &y);

        // If x < y, then we just make it with 2 pieces
        if (x < y){
            printf ("%d 2 %d %d\n", num, x, y);
        }

        // Note that the line segments has to increase by 1 each time.
        // I.e the lowest y we can reach is 4.
        else if (y >= 4 && x-y+5 > 3 && x-y+5 < x+2){
            printf("%d 6 1 2 3 %d %d %d\n", num, x-y+5, x+2, x+3);
        }

        // Else no path
        else {
            printf ("%d NO PATH\n", num);
        }
    }
    return 0;
}

// Case 2 explanation
// Suppose O is the origin, T is the Target.
// Note that we cannot get to T with only 2 line segments, so we have to go
// around the origin.
// We don't want to go too far away, so we will use line segment 1 2 3 for the
// first 3. This puts us at point A, which is at coordinates (-2, 2)
//
// Work backwards from T. Suppose T is at (x, y). Suppose the shortest length of
// the last section is a. Then point C needs to be (x, y-a).
//
// Next, the line segment connecting B to C should be length a-1. This will
// result in the shortest path going. (This is proven below)
// That will put point B at (x-a+1, y-a).
//
// However, we know that the x-coordinate of B is that of A.
// i.e. x-a+1 == -2
// Mathematics, we have a = x+3. That gives us the length of B-C and C-T
//
// Lastly, what about A-B? Suppose the length of A-B is q.
// Then the y coordinate of B = 2-q = y-x-3
// i.e. q = x-y-5.
//
// BUT: Note that q needs to be longer than 3 (the previous length), yet shorter
// than x+2 (the length of B-C). This is a check that we do.
//
//       |
//       |        T
//     Axxx       x
//     x |x       x
//-----x-Ox-------x--
//     x |        x
//     x |        x
//     x |        x
//     BxxxxxxxxxxC
//       |
//

// Proof on why B-C should be a-1:
// Suppose B-C is has a length of a-k, k > 0.
// Then we will have, at x coord of A and B: -2 = x-a+k, a = x + 2+k.
// We then have, length of A-B: 2-q = y-x-2-k
// i.e. q = x-y+k+4
//
// Note that the lengths are now given by
// A-B: x-y + (k+4)
// B-C:   x + 2
// C-T:   x + (k+2)
//
// The total lengths will be minimized when k is minimised.
// Hence choose k = 1.
