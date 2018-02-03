#include <stdio.h>
#include <math.h>

int main(){
    long long zei[10000], a, c, b, st, ed, p1, p2, p3, p4;
    zei[0] = 13562946179651;  // Cheating at its best
    zei[1] = 1136972771;      // Granted these are with 5 prime multiples
    zei[2] = 190516135648213; // I mean, I could have written it
    zei[3] = 409765562434747; // But 19 extra lines to save 4 guys? Nah. Not worth it.
    zei[4] = 717429818501;    // This guy is 6 primes. Another 19 lines just for him??
    int g=-1, h=0, i, j, k, v=5, cunt, flag, num, plist [80000], somelist[120000] = {0};
    double d1, d2, d3, d4;
    somelist [0] = somelist[1] = 1;
    for (i=0; i<110000; i++){
        if (somelist[i] != 0){
            continue;
        }
        g++;
        plist[g] = i;
        for (j=i; j<110000/i; j++){
            somelist[j*i] = 1;
        }
    }

    for (i=0; i<5525; i++){ // Plateaus at 5520, but I like to be cautious
        p1 = plist[i];
        for (j=0; j<g; j++){
            if (j==i){
                continue;
            }
            p2 = plist[j];
            c = p2-p1, b = p1-1;
            if (c%b != 0){
                continue;
            }
            a = c/b;
            b = p1-a;
            p3 = p2*a + b;
            flag = 0;
            for (k=0; k<g; k++){
                if (p3%plist[k] == 0){
                    if (p3!=plist[k]){
                        flag = 1;
                    }
                    break;
                }
            }
            if (flag == 1){
                continue;
            }
            d1 = log10(p1);
            d2 = log10(p2);
            d3 = log10(p3);
            if (d1 + d2 + d3 > 15.0){
                continue;
            }
            zei[v] = p1*p2*p3;
            v++;
            p4 = p3*a+b;    //  Copy Pasta. Sigh 19 lines...
            flag = 0;
            for (k=0; k<g; k++){
                if (p4%plist[k] == 0){
                    if (p4!=plist[k]){
                        flag = 1;
                    }
                    break;
                }
            }
            if (flag == 1){
                continue;
            }
            d4 = log10(p4);
            if (d1 + d2 + d3 + d4 > 15.0){
                continue;
            }
            zei[v] = p1*p2*p3*p4;
            v++;
        }
    }
    scanf("%d", &num);
    while (num--){
        cunt = 0;
        scanf ("%lld %lld", &st, &ed);
        for (i=0; i<9607; i++){
            if (zei[i] <= ed && zei[i] >= st){
                cunt++;
            }
        }
        printf ("%d\n", cunt);
    }
    return 0;
}
