#include<iostream>

int sum (int N) {
    return (N*(N+1))/2;

}


int main(){
    std::ios::sync_with_stdio(false);

    int numcases, N, testcase;

    std::cin >> numcases;

    while (numcases > 0){
        std::cin >> testcase >> N;
        std::cout << testcase << ' ' << sum(N) << ' ' << sum(N)*2 - N << ' ' << sum(N)*2 << std::endl;
        numcases -= 1;
    }

    return 0;
}
