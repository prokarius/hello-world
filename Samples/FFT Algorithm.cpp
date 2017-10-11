#include <cstdio>
#include <vector>
#include <complex>
#include <cmath>

#define PI 3.141592653589793238462643383279L

typedef std::complex <long double> complex;
typedef std::vector<complex> list;
#define variable 262144

// The FFT algo is below
list fft(list a, long long m, complex w){
    // if the list has 1 element, then return it
    if (m == 1) return list(a);

    // if not, create two lists to store even and odd coeffs
    list ae, ao;
    for (long long i = 0; i < m/2; ++i){
        ae.push_back(a[2*i]);
        ao.push_back(a[2*i+1]);
    }
    // Create two more lists to store the fft version of both lists
    list fe, fo, F(m,0);
    fe = fft (ae, m/2, w*w);
    fo = fft (ao, m/2, w*w);

    // Then do some mumbo jumbo and return the final list F
    complex x = 1.0;
    for (long long j=0; j< m/2; ++j){
        F[j] = fe[j] + x*fo[j];
        F[j+m/2] = fe[j] - x*fo[j];
        x *= w;
    }
    return F;
}

int main(){
    // Initialise our shit
    long long i, N;
    long long counter=0;
    scanf ("%lld", &N);
    list P, Q(variable, 0), ph, outputlist;
    std::vector<long long> T(150006,0);
    
    // Read input and store into polynomial list
    for (i=0; i<N; ++i){
        long long input;
        scanf("%lld", &input);
        Q[input+50000] = Q[input+50000] + complex (1,0);
    }
    complex w(cos(2*PI/variable), sin(2*PI/variable));

    // FFT to go into frequency domain and calculate convolution shit
    ph = fft(Q, variable, w);
    for (i=0; i<variable; ++i) outputlist.push_back(ph[i]*ph[i]);

    // FFT to come back into time domain and clean data
    P = fft (outputlist, variable, complex (1.0)/w);
    for (i=50000; i<= 150000; ++i) T[i]=(long long)(0.5 + P[i].real()/variable);

    // Your other code here
}
