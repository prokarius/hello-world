#include<stdio.h>
#include<math.h>

#define EPSILON 1e-8
#define Math_PI 3.141592653589
#define MAX(x, y) (x > y)?(x):(y)
#define MIN(x, y) (x < y)?(x):(y)

double a, b, c;

double cosineRule(double x, double y, double side){
    // If the side length is too big that the other 2 sides can't span it
    // then return a large ass number so we know to decrease it
    if (side > x + y - EPSILON) return 10007;

    // If the side length is too small that it add with the smaller of lengths
    // cannot span the larger length, then return a small ass number so we know to
    // increase it
    if (side + (MIN(x, y)) - EPSILON < (MAX(x, y))) return -10007;

    // Do the cosine rule shit
    double angle = acos((x*x + y*y - side*side) / (x * y * 2));

    // Check that the angle is positive
    if (angle < 0.0) angle += Math_PI*2;
    return angle;
}


// Return 1 if the central angle < 2 pi radians else 0
int check(double side){
    if (cosineRule(a, b, side) + cosineRule(b, c, side) + cosineRule(c, a, side) < Math_PI * 2){
        return 1;
    }
    return 0;
}

int main(){
    // Scan in input
    scanf("%lf %lf %lf", &a, &b, &c);

    // We will do binary search
    double lo = 0;
    double hi = 1000;
    double mid;

    while (hi - lo > EPSILON){
        mid = lo + (hi - lo)/2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }

    // DUCT TAPE
    // Check that we are not dealing with an alien carpet
    double testab = cosineRule(a, b, mid);
    double testbc = cosineRule(b, c, mid);
    double testca = cosineRule(c, a, mid);
    if (testab == 10007 || testab == -10007 ||
        testbc == 10007 || testbc == -10007 ||
        testca == 10007 || testca == -10007){
        printf("-1\n");
        return 0;
    }

    // DUCT TAPE
    // One more check: mid should theoretically be longer than all 3 side lengths
    if (a > mid + EPSILON || b > mid + EPSILON || c > mid + EPSILON){
        printf("-1\n");
        return 0;
    }

    // OK we are done with the binary search. Area of an equilateral triangle with
    // side length a = a*a*sqrt(3)/4 = a**2 * 0.43301270189 (google)
    printf("%.3lf\n", mid*mid*0.43301270189);
    return 0;
}
