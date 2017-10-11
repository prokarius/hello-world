/*

// Triangles (Interlocking Triangles in 3D space)

#include <stdio.h>
#include <math.h>
#define EPSILON 1e-5

typedef struct triangle triangle;
typedef struct plane plane;
typedef struct point point;

struct point{
    // A point is defined by its 3 coordinates
    double x, y, z;
};

struct triangle {
    // A triangle is defined by its three points
    point px, py, pz;
};

struct plane {
    // A plane is defined by its normal vector, and 3 points on it
    double vx, vy, vz;
    triangle t;
};

point subtract (point a, point b){
    // Returns the vector pointing from a to b. i.e. a-b
    point ans;
    ans.x = a.x - b.x;
    ans.y = a.y - b.y;
    ans.z = a.z - b.z;
    return ans;
}

point poi (plane p, point a, point b){
    // Returns the point of intersection of line a->b with plane p
    // We create another point instance for pretend is a vector
    // That will become the normal vector of our plane
    point vec = subtract (b, a), ans;
    double d = (p.t.px.x - a.x)*p.vx + (p.t.px.y - a.y)*p.vy +(p.t.px.z - a.z)*p.vz;
    d /= (vec.x*p.vx + vec.y*p.vy + vec.z*p.vz);
    ans.x = d*vec.x + a.x;
    ans.y = d*vec.y + a.y;
    ans.z = d*vec.z + a.z;
    return ans;
}

double aria (point p1, point p2, point p3){
    // Calculates the area of the triangle defined by the three points
    double a, b, c;
    point v1 = subtract (p1, p3), v2 = subtract (p2, p3);
    a = v1.x*v2.y - v1.y*v2.x;
    b = v1.y*v2.z - v1.z*v2.y;
    c = v1.z*v2.x - v1.x*v2.z;
    return 0.5 * sqrt(a*a + b*b + c*c);
}

int intersect (point p, triangle t){
    // Returns 1 if p lies in t, else returns 0
    // p is assumed to be on the plane of t
    double areatri = aria (t.px, t.py, t.pz), sumarea=0;
    sumarea += aria (t.px, t.py, p);
    sumarea += aria (t.py, t.pz, p);
    sumarea += aria (t.px, t.pz, p);
    if (fabs(sumarea-areatri) < EPSILON) return 1;
    return 0;
}

int checkline (point p, point l1, point l2){
    // Returns 1 if p in on line l1 - l2
    // If error is small, then let it slide
    point linevec = subtract (l2, l1);
    point pl = subtract (p, l1);

    double n = pl.x/linevec.x;
    if (n > 1) return 0;
    if (n < 0) return 0;
    if (fabs ((pl.y/linevec.y) - n) > EPSILON) return 0;
    if (fabs ((pl.z/linevec.z) - n) > EPSILON) return 0;
    return 1;
}

int check (point p, triangle t){
    // Returns 1 if p in triangle by checking each pair of line with the point
    if (checkline (p, t.px, t.py)) return 1;
    if (checkline (p, t.py, t.pz)) return 1;
    if (checkline (p, t.pz, t.px)) return 1;
    return 0;
}

int main(){
    int n, j;
    double array[20];
    plane pta;
    triangle a, b;
    point pointa, pointb, p[6], inters[3];
    scanf ("%d", &n);
    for (j=0; j<n; ++j){
        // Scan in the coordinates
        int i = 0;
        for (i=0; i<18; ++i) scanf("%lf", &array[i]);
        for (i=0; i<6; ++i){
            p[i].x = array[3*i];
            p[i].y = array[3*i+1];
            p[i].z = array[3*i+2];
        }

        // Make the two triangles
        a.px = p[0];
        a.py = p[1];
        a.pz = p[2];
        b.px = p[3];
        b.py = p[4];
        b.pz = p[5];

        // Find plane of triangle a
        point vec1 = subtract(a.px, a.pz), vec2 = subtract (a.py, a.pz);
        pta.t = a;
        pta.vx = vec1.y*vec2.z - vec1.z*vec2.y;
        pta.vy = vec1.z*vec2.x - vec1.x*vec2.z;
        pta.vz = vec1.x*vec2.y - vec1.y*vec2.x;

        // Find intersection points of the plane
        inters[0] = poi (pta, b.px, b.py);
        inters[1] = poi (pta, b.px, b.pz);
        inters[2] = poi (pta, b.py, b.pz);

        // Shit, one of these is not the correct point
        // Could be the case that the projection of points intesects well
        // Hence this nested shit
        if (check (inters[0], b)){
            pointa = inters[0];
            if (check (inters[1], b)){
                pointb = inters[1];
            }
            else {
                if (check (inters[2], b)){
                    pointb = inters[2];
                }
                else {
                    printf("NO\n");
                    continue;
                }
            }
        }
        else {
            if (check (inters[1], b)){
                pointa = inters[1];
                if (check (inters[2], b)){
                    pointb = inters[2];
                }
                else {
                    printf("NO\n");
                    continue;
                }
            }
            else {
                printf("NO\n");
                continue;
            }
        }
        // Find out if one in one out:
        int k = 0;
        k += intersect (pointa, a);
        k += intersect (pointb, a);
        if (k == 1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}



*/

// JUST A FEW MORE TRIANGLES

#include<stdio.h>

long long array[500005];
// array[n] = number of i such that i^2 == n
// Well, we will be using this a lot, n will change, depending where we are
// Hence you will see a lot of cleaning

long long thething (long long p, long long expo){
    // Number of solutions for a^2 + b^2 = c^2 (mod p^expo)
    // But if exponent = 0, then there is only trivial solution
    if (expo == 0) return 1;
    long long n=1, i, sq, output = 0;
    // Wait what is p^e again?
    for (i = 0; i< expo; ++i) n *= p;
    // Clean and populate our array with _Quadratic Residues_ of all i < n
    // See: http://www.math.brown.edu/~jhs/MA0042/FRINTNewCh2324.pdf
    for (i=0; i<n; ++i) array[i] = 0;
    for (i=0; i<n; ++i) ++array[i*i % n]; 

    // 3 cases: CASE 1) When a != 0 (mod p) AND b != 0 (mod p)
    //        : CASE 2) When a != 0 (mod p) XOR b != 0 (mod p)
    //        : CASE 3) When 2 == 0 (mod p) AND b == 0 (mod p)
    // We need to deal with them seperately

    // CASE 1) Get the pairwise multiplication of all quadratic residues
    // This is kinda like FFT. We can do this in O(n) time cuz of symmetry.
    // So how to cheat? Well, assume b^2 == 1^* (mod p)
    // Now we find the number of ways a^2 + 1 == c^2 (mod p)
    for (i=0; i<n; ++i) output += array[i]*array[(i+1)%n];

    // CASE 2) When p divides either one of a^2 or b^2
    // WLOG, assume p divides a^2. Again, assume b^2 == 1^* (mod p)
    // Then divide a^2 by p, and loop. (Or iterate for i=0 to n, i+=p)
    // Same thing, we find number of ways a^2 + 1 == c^2 (mod p) 
    for (i=0; i<n; i+=p){
        sq = (i*i+1)%n;
        output += array[sq];
    }
    // For CASE 1 & 2, we can find a modulo inverse q such that q*(x-y) = 1
    // From here we can multiply q by any of 1 - p-1 to get all p-1 values
    // i.e. We have assumed a^2 == 1 (mod p), we need to generalise this
    // And since there are (p-1) other ways this can happen:
    // i.e. There are (p-1) equivalent classes
    // ^*This is why we could have replaced 1 in line 29 with any other int
    output *= (p-1);

    // If n = p^x, then every (n/p), this pattern will repeat
    output *= (n/p);

    // CASE 3) has 2 cases:
    // CASE 3a) What if expo > 1?
    // When i%p == 0, there will be p distinct i such that i^2 == 0 (mod p)
    // => All n for i = 0 (mod p) && i = n (mod p) has the same solution
    // So we divide each of the a,b,c by p, and find the number of solutions
    // Since there will be p repetitions, for a,b,c, we multiply by p^3
    if (expo > 1) output += thething (p, expo-2)*p*p*p;
    // CASE 3b) Else, we just have to account for a=b=c=0, so +1.
    else ++output;
    return output;
}

long long diag (long long n){
    // Number of solutions when a^2 = b^2. i.e. along the diagonal
    long long i, output=0;
    for (i=1; i<n; ++i){
        // a=i, b=i, c=2*i*i%n
        output += array[(2*i*i)%n];
    }
    return output;
}

long long zero (long long n){
    // Number of solutions when a, b or c is 0
    long long i, output=0;
    for (i=0; i<n; ++i){
        // a=i, b=0, c=i
        // x2 because a and b can swap places
        output += 2 * array[i] * array[i];
        // a=i, b=n-i, c=0
        // no need x2 because when i++, a will defo == n-i
        output += array[i] * array[(n-i)%n];
    }
    // when any 2 of a,b,c are 0s, 3*(# of 0s) ways to happen
    output += 3 * array[0]; 
    // when all 3 of a,b,c are 0s. 1 way to happen
    output += 1;
    return output;
}

int main(){
    long long i, n, ph, output = 1;
    scanf("%lld", &n);
    // Oh, we will be modifying n, so create a new variable to hold n.
    ph = n;
    // Anyways, we prime factorize n and multiply the results together
    // Why this works is due to Chinese Remainder Theorem
    // Incidentally we don't bother sieving because it wastes time   
    for (i=2; i*i<=ph; ++i){
        if (ph%i == 0){
            // See, i will be the current smallest prime that divides ph
            // We want to find out the smallest prime decomp
            // Hence divide by i all the way until i doesn't divide anymore
            int expo=0;
            while (ph%i == 0){
                expo += 1;
                ph /= i;
            }
            // So because quad residues are multiplicative
            // We can just multiply the prime factors together
            // i.e. output_ab = output_a * output_b
            output *= thething (i, expo);
        }
    }
    // OK we are done with the bulk of the factorizing BUT
    // What if there is still stuff left over in ph? Let's deal with it!
    if (ph != 1){
        output *= thething (ph, 1);
    }
    // So we counted all the ways we can have a^2 + b^2 = c^2 mod (n)
    // This is including when a,b,c=0, and when b > a
    // Let's get rid of those extra solutions

    // First we clean and populate our array:
    for (i=0; i<n; ++i) array[i] = 0;
    // Notice we don't count 0^2 in there. Because it's the trivial value.
    for (i=1; i<n; ++i) ++array[i*i % n];
    // Then get rid of all the zeros:
    output -= zero(n);
    // Notice the grid is symmetric about the main diagonal
    // Hence we add one more copy of the main diagonal and divide 2
    output += diag(n);
    printf ("%lld\n", output/2);
    return 0;
}

