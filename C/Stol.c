#include<stdio.h>
#define MAX(x,y) (x>y)?(x):(y)

int array[1002], stack[1002];

int main(){
    char ph;
    int R, C, R2, i, best=0, peri, h, stackH;
    scanf ("%d %d", &R, &C);
    R2 = R;

    // I'm gonna set up some stuff here. This will help a bit later
    array[0] = -1;
    stackH = 1;

    // For each line of input, we do the histogram method
    // This would save a bit of space, and not really bother with preprocessing.
    while (R2--){
        i=0;
        while (++i <= C){
            scanf(" %c", &ph);

            // If the input character is a X, set the entry to 0.
            // Else add one to it.
            if (ph == '.') ++array[i];
            else array[i] = 0;
        }

        // Now, we do the histogram test on the newly formed array
        // Essentially, we are trying to find the biggest rectangle with the
        // base as the current row.
        // Oh, the histogram problem is when we want to find out the area of the
        // largest rectangle in a given histogram. Solution will be described.

        i = 1;
        while (i<=C){
            // If the value is larger than stack.top, we push index into the stack
            // I set array[0] = -1, so I never need to care about overflows
            // I set stackH = 1, so I never have to check for empty stack
            if (array[i] >= array[stack[stackH-1]]){
                stack[stackH] = i++;
                ++stackH;
            }
            // Else, we pop from the stack and calculate the perimeter
            // pretending the last popped element was the tallest.
            // The rectangle calculated has the popped element as the left index
            // and the right most element is the current element that we push
            // Keep doing this in the while loop until we are taller.
            else{
                h = stack[--stackH];
                peri = 2*array[h] + 2*(i-1 - stack[stackH-1]);
                best = MAX(best, peri);
            }
        }

        // OK we are at the end of the histogram.
        // We should still have stuff in our stack.
        // Pop it and calculate the perimeter
        // Note that a rectangle with side 0 is not a rectangle!!
        while (stackH-1 > 0){
            h = stack[--stackH];
            if (array[h]){
                peri = 2*array[h] + 2*(i-1 - stack[stackH-1]);
                best = MAX(best, peri);
            }
        }
    }

    // Finally print out what the best is.
    // Don't forget to minus 1. Don't be stupid :D
    printf ("%d\n", best-1);
    return 0;
}
