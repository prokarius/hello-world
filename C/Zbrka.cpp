#include<iostream>

int main (){
    std::ios::sync_with_stdio(false);
    long long N, C;
    std::cin >> N >> C;

    long long sumvalue [N+1][C+2]; // sum to the C-1th item in the list.
    long long dp [N+1][C+1]; // number of possible arrangements

    for (int i = 0; i < N+1; i ++){
        for (int j = 0; j < C+1; j++){
            sumvalue[i][j] = 0;
            dp [i][j] = 0;
        }
    }
    dp [0][0] = 1;

    for (int i = 0; i < N; i++){
        sumvalue [i][C+1] = 0;
    }

// I have made everything into zeroes ^.

    for (int i = 1; i < C+2; i ++){
        sumvalue [0][i] = 1;
    }

    for (int i = 1; i < N+1; i ++){
        sumv, subtracts;
        sumv = 0;
        subtracts = 0;
        for (int j = 1; j < C+2; j++){
            subtracts = j - i;
            if (subtracts < 0){
                subtracts = 0;
            }
            dp[i][j-1] = (1000000007 + sumvalue[i-1][j]-sumvalue[i-1][subtracts])%1000000007;
            sumv += (sumvalue[i-1][j]-sumvalue[i-1][subtracts])%1000000007;
            sumvalue [i][j] = sumv;

        }
    }
    std::cout << dp[N][C];

    return 0;
}
