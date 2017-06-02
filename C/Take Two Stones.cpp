#include<iostream>

int main()
{
    std::ios::sync_with_stdio(false);

    std::string winner;
    int stones;
    std::cin >> stones;
    if (stones %2 == 1){
        winner = "Alice\n";
    }
    else {
        winner = "Bob\n";
    }
    std::cout << winner;
    return 0;
}
