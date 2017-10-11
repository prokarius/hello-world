#include <stdio.h>

int plist [3430], somelist[32000] = {0};

// Standard Prime Generator. Copy this shit.
void setting() {
    int g=-1, i ,j;
    somelist [0] = somelist[1] = 1;
    for (i=0; i<32000; ++i){
        if (somelist[i] != 0){
            continue;
        }
        plist[++g] = i;
        for (j=i; j<32000; j+=i){
            somelist[j] = 1;
        }
    }
}

long long f(long long a, long long o){
    long long i = 1, j=a, p=o;
    while (p){
        if (p%2==1) i=(i*j)%o;
        j = (j*j) % o;
        p = p >> 1;
    }
    return i;
}

int test(long long p, long long a){
    int i;
    for (i=0; i<3428; ++i){
        if (p % plist[i] == 0){
            if (p == plist[i])return 0;
            if (f(a,p) == a) return 1;
            return 0;
        }
    }
    return 0;
}

int main(){
    setting();
    long long p, a;
    scanf("%lld %lld", &p, &a);
    while (p != 0 && a!=0){
        test (p, a) ? printf("yes\n"):printf ("no\n");
        scanf ("%lld %lld", &p, &a);
    }
    return 0;
}
