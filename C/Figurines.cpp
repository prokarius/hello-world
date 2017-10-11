#include <cstdio>
#include <vector>
#include <complex>
#include <cmath>

#define MIN(x,y) (x<y)?(x):(y)
#define MAX(x,y) (x>y)?(x):(y)

#define PI 3.141592653589793238462643383279L

typedef std::complex <long double> complex;
typedef std::vector<complex> list;
#define variable 262144

list fft(list a, long long m, complex w){
    if (m == 1) return list(a);

    list ae, ao;
    for (long long i = 0; i < m/2; ++i){
        ae.push_back(a[2*i]);
        ao.push_back(a[2*i+1]);
    }
    
    list fe, fo, F(m,0);
    fe = fft (ae, m/2, w*w);
    fo = fft (ao, m/2, w*w);

    complex x = 1.0;
    for (long long j=0; j< m/2; ++j){
        F[j] = fe[j] + x*fo[j];
        F[j+m/2] = fe[j] - x*fo[j];
        x *= w;
    }
    return F;
}

int main(){
    long long i, N;
    long long counter=0, min=9999999, max=-1, sum=0;
    scanf ("%lld", &N);
    list P, P2, Q(variable/2, 0), ph, outputlist, outputlist2, T(variable, 0);
    
    for (i=0; i<N; ++i){
        long long input;
        scanf("%lld", &input);
        Q[input] = Q[input] + complex (1,0);
        min = MIN(min, input);
        max = MAX(max, input);
        sum += input;
    }
    complex w(cos(4*PI/variable), sin(4*PI/variable));

    ph = fft(Q, variable/2, w);
    for (i=0; i<variable/2; ++i) outputlist.push_back(ph[i]*ph[i]);

    P = fft (outputlist, variable/2, complex (1.0)/w);
    for (i=0; i< 120000; ++i){
        if((0.5 + 2*P[i].real()/variable) > 1) T[i] = complex (1, 0);
        else T[i] = complex(0, 0);
    }

    complex w2(cos(2*PI/variable), sin(2*PI/variable));

    ph = fft (T, variable, w2);
    for (i=0; i<variable; ++i) outputlist2.push_back(ph[i]*ph[i]);

    P2 = fft (outputlist2, variable, complex (1.0)/w2);
    for (i=0; i<variable; ++i){
        if ((0.5 + P2[i].real()/variable) > 1) ++counter;
    }

    printf ("%lld %lld %lld %lf\n", max*4, min*4, counter, (4.0*sum)/N);
}
