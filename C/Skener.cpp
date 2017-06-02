#include<iostream>

int main (){
    std::ios::sync_with_stdio(false);

    std::string placeholder;
    int rows, cols, numrows, numcols;

    std::cin >> rows >> cols >> numrows >> numcols;
    while (rows != 0){
        std::cin >> placeholder;
        std::string outputstr;
        for (int i = 0; i < placeholder.length(); i++){
            for (int k = 0; k < numcols; k ++){
                outputstr += placeholder[i];
            }
        }
        outputstr += "\n";
        for (int j = 0; j < numrows; j++){
            std::cout << outputstr;
        }
        rows -= 1;
    }
    return 0;
}
