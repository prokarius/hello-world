#include <stdio.h>

long long choosen (long long n){
    if (n < 3){
        return 0;
    }
    long long output = (n*(n-1)*(n-2))/6;
    return output;
}

void cod(int testcase){
    long long n, a, b, c, d, x, y, m, output=0, cunt = 0;
    long long box[9] = {0};
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &n, &a, &b, &c, &d, &x, &y, &m);
    box[(x%3)*3+y%3] += 1;
    for (cunt = 1; cunt < n; cunt++){
        x = (a * x + b) %m;
        y = (c * y + d) %m;
        box[(x%3)*3+y%3] += 1;
    }
    int test;
    for (test = 0; test < 9; test ++){
        output += choosen(box[test]);
    }
    output += box[0]*box[4]*box[8];
    output += box[0]*box[5]*box[7];
    output += box[1]*box[3]*box[8];
    output += box[1]*box[5]*box[6];
    output += box[2]*box[4]*box[6];
    output += box[2]*box[3]*box[7];
    output += box[0]*box[1]*box[2];
    output += box[3]*box[4]*box[5];
    output += box[6]*box[7]*box[8];
    output += box[0]*box[3]*box[6];
    output += box[1]*box[4]*box[7];
    output += box[2]*box[5]*box[8];
    printf("Case #%d: %lld\n", testcase+1, output);
}

int main(){
    int numtest, counter = 0;
    scanf("%d", &numtest);
    while (counter < numtest){
        cod (counter);
        counter += 1;
    }
    return 0;
}
