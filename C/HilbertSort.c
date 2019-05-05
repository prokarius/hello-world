#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned char strings[10000005];

int cmpfunc(const void* a, const void* b){
    char* str1 = (char*)a;
    char* str2 = (char*)b;

    return strcmp(str1, str2);
}

// Makes a string that represent the path of the hilbert curve
void makeHilbert(double x, double y, double size, int depth, int currNode){
    // If we have reached depth of 31, terminate the string with null
    // Why 31? Because the input is as big as 1B = 2**30
    // Then I add 1 because I can. (Jk it's to make it easy to calculate array index)
    if (depth == 31){
        strings[(currNode << 6) + depth] = 0;
        return;
    }
    double newSize = size/2;
    
    // Lets see where in the curve this point goes to:
    if (x <= newSize && y <= newSize){
        strings[(currNode << 6) + depth] = 'D';

        // Note that we flip y and x, because the curve is flipped here
        makeHilbert(y, x, newSize, depth + 1, currNode);
        return;
    }
    if (x <= newSize && y > newSize){
        strings[(currNode << 6) + depth] = 'e';
        makeHilbert(x, y - newSize, newSize, depth + 1, currNode);
        return;
    }
    if (x > newSize && y > newSize){
        strings[(currNode << 6) + depth] = 'k';
        makeHilbert(x - newSize, y - newSize, newSize, depth + 1, currNode);
        return;
    }
    else {
        strings[(currNode << 6) + depth] = 'u';

        // Flip y and x here too, also note the math.
        makeHilbert(newSize - y, size - x, newSize, depth + 1, currNode);
        return;
    }
}

int main(){
    // Scan in input
    int n;
    double s;
    scanf("%d %lf", &n, &s);

    for (int i = 0; i < n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);

        // Make the string
        makeHilbert(x, y, s, 0, i);

        // Push the x and y values into the array too!
        for (int j = 0; j < 4; ++j){
            strings[(i << 6) + j + 40] = x & 0xff;
            strings[(i << 6) + j + 50] = y & 0xff;
            x >>= 8;
            y >>= 8;
        }
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < 64; ++j){
            printf("%d ", strings[(i << 6) + j]);
        }
        printf("\n");
    }

    // QSORT
    qsort(strings, n, sizeof(char)*64, cmpfunc);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < 64; ++j){
            printf("%d ", strings[(i << 6) + j]);
        }
        printf("\n");
    }

    // Print out the numbers in order
    for (int i = 0; i < n; ++i){
        int x = 0;
        int y = 0;

        for (int j = 3; j >= 0; --j){
            x <<= 8;
            y <<= 8;
            x += strings[(i << 6) + j + 40];
            y += strings[(i << 6) + j + 50];
        }

        printf("%d %d\n", x, y);
    }

    return 0;
}
