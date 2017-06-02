#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

#define PI 3.14159265358979323846L

typedef std::complex <long double> V;
typedef std::vector<V> S;
#define variable 524288

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

int main(){
    int N, M, counter = 0;
    std::cin >> N;
    S P, Q(variable, 0), newd1, outputlist;
    std::vector <int> R(400000,0), T(400000,0);
    for (int i=0; i<N; i++){
        int input;
        std::cin >> input;
        Q[input] = 1;
    }
    Q[0] = 1;
    std::cin >> M;
    for (int i=0; i<M; i++){
        int input;
        std::cin >> input;
        R[input]++;
    }
    V w(cos(2*PI/variable), sin(2*PI/variable));
    newd1 = fft(Q, variable, w);
    for (int i=0; i<variable; i++){
        outputlist.push_back(newd1[i]*newd1[i]);
    }
    P = fft (outputlist, variable, V(1.0)/w);

    for (int i=0; i<= 200000; i++){
        long double b = 0.3 + P[i].real()/variable;
        if ((int)b > 0){
            T[i] = 1;
        }
    }
    for (int i = 0; i<=200000; i++){
        if (T[i] > 0){
            if (R[i] >0){
                counter += R[i];
            }
        }
    }
    std::cout << counter;
}
