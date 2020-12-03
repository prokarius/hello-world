#include<cstdio>
#include<cstring>
#include<deque>

char command[16];

int main(){
    int n;
    scanf("%d", &n);

    // Apparently cpp deques have O(1) random access :0
    std::deque<int> first_half;
    std::deque<int> second_half;

    // Process each input seperately
    for (int i = 0; i < n; ++i){
        int x;
        scanf(" %s %d", command, &x);

        switch(command[strlen(command)-2]){
            case('c'): // push_baCk
                second_half.push_back(x);

                // Redistribute
                if (second_half.size() > first_half.size()){
                    int y = second_half.front();
                    second_half.pop_front();
                    first_half.push_back(y);
                }
                break;
            case('n'): // push_froNt
                first_half.push_front(x);    

                // Redistribute
                if (first_half.size() > second_half.size() + 1){
                    int y = first_half.back();
                    first_half.pop_back();
                    second_half.push_front(y);
                }
                break;
            case('l'): // push_middLe
                if (first_half.size() == second_half.size()) first_half.push_back(x);
                else second_half.push_front(x);
                break;
            case('e'): // gEt
                if (x < first_half.size()) printf("%d\n", first_half[x]);
                else printf("%d\n", second_half[x - first_half.size()]);
                break;
        }
    }

    return 0;
}

