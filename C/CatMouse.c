#include<stdio.h>
#include<math.h>

#define PI 3.1415926535898

// Well, this is a famous problem... Referenced here...
// https://puzzling.stackexchange.com/questions/2155/the-lake-monster

// I really did do the math during Ricardo class. Please trust me?

// OK fine you don't. The simple solution is this:
// The mouse will run directly opposite the cat until a certain radius r.
// This radius is essentially the ratio of the cat to mouse speed, because at that
// radius, the angular velocity of the mouse equals the cat.

// Now the mouse has to make a mad dash for the edge!!
// The mouse should run tangent to the outer circle, in the direction that the
// cat chases. Even though dashing directly for the edge makes sense, in this
// case, the cat has to run longer too, which makes it fractionally faster.

int main(){
    // Scan in input
    int testcases;
    scanf("%d", &testcases);

    while(testcases--){
        double tom, jerry, R;
        scanf("%lf %lf %lf", &R, &tom, &jerry);

        double ratio = tom/jerry;

        // If the cat is slower
        if (ratio > 1){
            printf("YES\n");    
        }

        // The thing I mentioned above
        else if (sqrt(1 - ratio * ratio) <= ratio * (PI + (0.5*PI - asin(ratio)))){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    
    return 0;
}
