#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

#define PI 3.14159265358979323846L

typedef std::complex <long double> V;
typedef std::vector<V> S;

long long pad (int l){
    l -= 1;
    int counter = 0;
    while (l!=0){
        l >>= 1;
        counter += 1;
    }
    return 1LL<<counter;
}

S fft(S& a, int m, V w){
    if (m == 1){
        return S(a);
    }
    S ae, ao;
    for (int i = 0; i < m/2; i++){
        ae.push_back(a[2*i]);
        ao.push_back(a[2*i+1]);
    }
    S fe, fo, F(m,0);
    fe = fft (ae, m/2, w*w);
    fo = fft (ao, m/2, w*w);
    V x = 1.0;
    for (int j=0; j< m/2; j++){
        F[j] = fe[j] + x*fo[j];
        F[j+m/2] = fe[j] - x*fo[j];
        x *= w;
    }
    return F;
}

void code(){
    int a, b,c=0;
    S Q, R, P, newd1, newd2, outputlist;
    std::cin >> a;
    while (c++ <= a){
        long double x;
        std::cin >> x;
        Q.push_back(x);
    }
    c = 0;
    std::cin >> b;
    while (c++ <= b){
        long double x;
        std::cin >> x;
        R.push_back(x);
    }
    int piss = a + b + 1;
    long long variable = pad(piss);
    while (Q.size() < variable){
        Q.push_back(0);
    }
    while (R.size() < variable){
        R.push_back(0);
    }
    V w(cos(2*PI/variable), sin(2*PI/variable));
    newd1 = fft(Q, variable, w);
    newd2 = fft(R, variable, w);
    for (int i=0; i<variable; i++){
        outputlist.push_back(newd1[i]*newd2[i]);
    }
    P = fft (outputlist, variable, V(1.0)/w);
    std::cout << piss-1 << "\n";
    for (int i=0; i< piss; i++){
        long double b = 0.5 + P[i].real()/variable;
        if (b<0){
            b -= 1;
        }
        std::cout << (int)b << " ";
    }
}

int main (){
    int N;
    std::cin >> N;
    while (N--){
        code();
        std::cout << "\n";
    }

    return 0;
}
