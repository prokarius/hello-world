#include <stdio.h>
#define MIN(x, y) (((x)<(y)) ? (x):(y))

int main(){
    int f=1,p,a,b,c,d,ua,ub,uc,ud,x,y,y2,z;
    scanf ("%d %d %d %d %d", &p, &a, &b, &c, &d);
    ud = p/25;
    if (ud > d) {ud = d;}
    d -= ud;
    p -= ud*25;
    uc = p/10;
    if (uc > c) {uc = c;}
    c -= uc;
    p -= uc*10;
    ub = p/5;
    if (ub > b) {ub = b;}
    b -= ub;
    p -= ub*5;
    ua = p;
    if (ua > a) {ua = a;}
    a -= ua;
    p -= ua;
    
    // GREEDY

    if (p > 0){
        printf("Impossible");
        return 0;
    }
    while (f != 0){
        f = 0;
        if (ud >= 2 && c >= 5){ // 2*25 = 5*10
            printf("A");
            x = ud/2;
            y = c/5;
            z = MIN(x, y);
            ud -= z*2;
            c -= z*5;
            uc += z*5;
            f++;
        }
        if (ud >= 1 && c >= 2 && b >= 1){ // 1*25 = 2*10 + 1*5
            printf("B");
            x = ud;
            y = c/2;
            y2 = b;
            z = MIN(x, MIN(y, y2));
            ud -= z;
            c -= z*2;
            uc += z*2;
            b -= z;
            ub += z;
            f++;
        }
        if (ud >= 1 && c >= 1 && b >= 3){ // 1*25 = 1*10 + 3*5
            printf("C");
            x = ud;
            y = c;
            y2 = d/3;
            z = MIN(x, MIN(y, y2));
            ud -= z;
            c -= z;
            uc += z;
            b -= z*3;
            ub += z*3;
            f++;
        }
        if (uc >= 1 && b >= 1 && a >= 5){ // 1*10 = 1*5 + 5*1
            printf("D");
            x = uc;
            y = b;
            y2 = a/5;
            z = MIN(x, MIN(y, y2));
            uc -= z;
            c += z;
            b -= z;
            ub += z;
            a -= z*5;
            ua += z*5;
            f++;
        }
        if (ud >= 1 && a >= 25){ // 1*25 = 25*1
            printf("E");
            x = ud;
            y = a/25;
            z = MIN(x, y);
            ud -= z;
            a -= z*25;
            ua += z*25;
            f++;
        }
        if (uc >= 1 && b >= 2){ // 1*10 = 2*5
            printf("F");
            x = uc;
            y = b/2;
            z = MIN(x, y);
            uc -= z;
            c += z;
            b -= z*2;
            ub += z*2;
            f++;
        }
        if (uc >= 1 && a >= 10){ // 1*10 = 10*1
            printf("G");
            x = uc;
            y = b/10;
            z = MIN(x, y);
            uc -= z;
            c += z;
            a -= z*10;
            ua += z*10;
            f++;
        }
        if (ub >= 1 && a >= 5){ // 1*5 = 5*1
            printf("H");
            x = ub;
            y = a/5;
            z = MIN(x, y);
            ub -= z;
            b += z;
            a -= z*5;
            ua += z*5;
            f++;
        }
    }
    printf("%d", ua + ub + uc +ud);
    return 0;
}
