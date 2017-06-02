#include <stdio.h>
#include <vector>

struct bra{
    int left = 0;
    int right = 0;
} current;

int main(){
    std::vector<bra> vlist, phlist;
    current.left = 0;
    current.right = 0;
    char ch;
    while(scanf("%c", &ch) != EOF){
        bra phbra;
        phlist.push_back(current);

        for (int i = 0; i < phlist.size(); i++){
            phbra = phlist.back();
            phlist.pop_back();
            if (ch == '('){
                phbra.right += 1;
            }
            else if (ch == ')'){
                phbra.left += 1;
            }
            if (phbra.right <= phbra.left){
                vlist.push_back(phbra);
            }
            printf ("(%d, %d)\n", phbra.left,  phbra.right);
        }

        for (int i = 0; i<vlist.size(); i++){
            bra g = vlist.back();
            vlist.pop_back();
            phlist.push_back(g);
        }
        if (ch == '('){
            current.left += 1;
        }
        else if (ch == ')'){
            current.right += 1;
        }
    }

    printf("\n");

    if (phlist.size() > 0){
        for (int i=0; i<phlist.size(); i++){
            bra testi = phlist.back();

        printf ("(%d, %d)\n", testi.left, testi.right);

            phlist.pop_back();
            if (testi.left == testi.right){
                printf("possible\n");
                return 0;
            }
        }
        printf ("impossible");
    }
    else {
        printf ("impossible");
    }

    return 0;
}
