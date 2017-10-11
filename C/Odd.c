//
// ODD BINOMINAL COEFFICIENTS
//

/*

#include <stdio.h>

int main (){
    long long l=0, p=0, q[100], n, d=0, o=0, t=1;
    scanf ("%lld", &n);
    while (n){
        if (n%2 == 1){
            q[p] = d;
            p++;
        }
        d++;
        n = n >> 1;
    }
    while (p--){
        long long g = 1, f=0;
        while (f++ < p[q]){
            g *= 3;
        }
        o += t*g;
        t *= 2;
    }
    printf ("%lld", o);
    return 0;
}

*/

//
// ODD AND EVEN ZEROES
//

#include <stdio.h>

int main() {
    long long n, f[30], j=1, i;
    f[0] = 1;
    f[1] = 0;
    for (i = 1; i < 14; i++){
        f[2*i] = j*10 + f[2*(i-1)]*5;
        j*=25;
        f[2*i+1] = j - f[2*i];
    }
    // f(25^n) = 25^(n-1)*10 + f(25^(n-1))*5
    // Populate the list!

    scanf("%lld", &n);
    while (n != -1){
        n++;
        long long k[40], h=1, m=0, o=0, p=0;
        while (n){
            k[m] = n%5;
            n = n/5;
            m++;
        } // k is n in base 5
        m--;        
        for (i=0; i<m; i++){
            h *= 5;
        }
        while (m > 0){
            if (m%2 == 0){              //Let k[m] be x
                o += k[m]*f[m+(p%2)];   //If digit is %25 = 0, take x*f[value, parity]
            }
            else {
                o += (k[m]/2)*h;          //Else, add x/2*value
                if (k[m]%2 == 1){       //If this is odd
                    o += f[m-1+(p%2)]*5;    //Add 5*f[value/5, parity]
                    p++;               //Change Parity
                }
            }
            h /= 5;
            m--;
        }
        o += k[0]*((p+1)%2);
        printf ("%lld\n", o);
        scanf ("%lld", &n);
    }
    return 0;
}
