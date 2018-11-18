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
