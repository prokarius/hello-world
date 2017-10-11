#include <stdio.h>
#include <math.h>
#define ERROR 1e-14

int main () {
    double xs, ys, xf, yf, q , minsin=0, maxsin=1, dist;
    int n, j=0, i=0;
    double coords[10005], velo[10005];
    scanf ("%lf %lf %lf %lf %d", &xs, &ys, &xf, &yf, &n);
    while (i < n-1){
        scanf("%lf", &q);
        coords[i] = q;
        i++;
    }
    coords [i++] = yf;
    while (--i){
        coords[i] -= coords[i-1];
    }
    coords[0] -= ys;
    while (i < n){
        scanf("%lf", &q); 
        velo[i] = q;
        i++;
    }
    // OK, we have scanned everything into memory
    // Let the computation begin. 

    dist = fabs(xf-xs);
    // Insight: This is symetric about x => only positive values for theta
    // Insight: If we exceed over shot xcoord of the end, that is wrong
    
    double timeout=0;

    while (maxsin-minsin > ERROR){ // while we have not hit the final point yet
        double howhigh=0, nowsin = (maxsin + minsin)/2;
        timeout=0;
        for (i=0; i<n; i++){ // for each layer
            double lsin, lcos, hypo, ltime, nowhigh;
            lsin = nowsin*velo[i]/velo[0]; // Snell's Law
            if (lsin > 1){ // Too shallow
                howhigh = dist+1; // To trigger the too shallow angle below
                break;
            }
            lcos = sqrt(1 - lsin*lsin); //stupid rule
            hypo = (coords[i])/lcos; // C = A/H
            ltime = hypo/velo[i]; // t = d/v
            nowhigh = hypo*lsin; // O = H*S
            timeout += ltime;
            howhigh += nowhigh; // Counters to keep track
        }
        if (howhigh > dist){ // Too far right, reduce angle to be sharper
            maxsin = nowsin; // Make the max lower, so average is reduced
        }
        else { // Too far left, increase angle
            minsin = nowsin; // make min higher, increase average
        }
    }
    printf ("%.10lf\n", timeout);
    return 0;
}
