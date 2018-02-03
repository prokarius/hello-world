#include <stdio.h>

#define MAX(x,y) (((x)>(y))?(x):(y)) //Ever wonder why "cock" is spelt with two C's?
#define MIN(x,y) (((x)<(y))?(x):(y)) //Damnit C.

int output, xcord[20], ycord[20], n, k, maxx[20], maxy[20], minx[20], miny[20]; //global vars

//num_point is the point number we are adding
//num_boxes is the number of squares we already have
//min_size is the current minimum size
void calc(int num_point, int num_boxes, int min_size){
    if (num_boxes > k || min_size >= output){
        //If we used too many boxes or
        //If the current size is too big
        return;
    }
    if (num_point == n){
        //If we have put all the points already
        //Update output to the minimum value
        output = MIN(output,min_size);
        return;
    }
    int j;
    for (j=0; j<=num_boxes; j++){
        int pa,pb,pc,pd;
        pa = minx[j]; //Store the values first
        pb = maxx[j]; //Cuz we will be modifying the variables later
        pc = miny[j]; //Essentially keeping a save state of variables
        pd = maxy[j];

        minx[j] = MIN(minx[j], xcord[num_point]); //Modify the variables
        maxx[j] = MAX(maxx[j], xcord[num_point]); //minx[j] is the left boundary of
        miny[j] = MIN(miny[j], ycord[num_point]); //square j.
        maxy[j] = MAX(maxy[j], ycord[num_point]); //maxx = right, miny = down, maxy = up

        calc(num_point+1, MAX(num_boxes, j+1), MAX(min_size, MAX(maxx[j]-minx[j], maxy[j]-miny[j]))); // Recursion is RIR

        minx[j] = pa; //Restore the variables when we are done with RIR
        maxx[j] = pb;
        miny[j] = pc;
        maxy[j] = pd;
    }
}

void clean(){ //Reinitialise the global variables.
    int qq;
    output = 1000000;
    for (qq=0; qq<20; qq++){
        maxx[qq] = maxy[qq] = xcord[qq] = ycord[qq] = 0;
        minx[qq] = miny[qq] = 65000;
    }
}

int main(){
    int T, i=0;
    scanf("%d", &T);
    while (i++ < T){
        clean();
        int a = 0;
        scanf ("%d %d", &n, &k);
        while (a < n){
            scanf ("%d %d", &xcord[a], &ycord[a]);
            a++;
        }
        calc(0, 0, 0); // Kinda like Dee-Pee
        printf ("Case #%d: %d\n", i, output);
    }
    return 0;
}
