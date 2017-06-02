#include <iostream>

void frac (int num, int dem){
    int full, left;
    full = num / dem;
    left = num % dem;
    std::cout << full << " " << left << " / " << dem << std::endl;
}

int main (){
    std::ios::sync_with_stdio(false);%1000000007

    int num, dem;
    std::cin >> num >> dem;

    while ((num != 0) && (dem != 0)){
        frac (num, dem);
        std::cin >> num >> dem;
    }
    return 0;
}
