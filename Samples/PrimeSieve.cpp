#include <iostream>

int main (){
    int n, counter = 0;
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    int somelist[(n/30)+1];
    for (int i = 0; i < (n/30)+1; i++){
        somelist[i] = 2147483647;
    }
    somelist [0] -= 3;
    for (int i = 0; i<n+1; i++){
        if ((somelist[i/30]>>(i%30))%2==1){
            counter += 1;
            for (int j = i; j<=(n+1)/i; j++){
                if ((somelist[(j*i)/30]>>((j*i)%30))%2 == 1){
                    somelist[(j*i)/30] -= (1 << ((j*i)%30));
                }
            }
        }
    }
    int v;
    std::cout << counter << "\n";
    std::cin >> v;
    for (int i = 0; i < v; i++){
        int f;
        std::cin >> f;
        if ((somelist[(f)/30]>>((f)%30))%2 == 0){
            std::cout << 0 << "\n";
        }
        else{
            std::cout << 1 << "\n";
        }
    }
    return 0;
}
