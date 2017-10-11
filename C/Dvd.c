#include <stdio.h>

int main(){
    int numpass;
    scanf ("%d", &numpass);
    while (numpass != 0){
        int numdvd, counter, curnum = 1;
        scanf("%d", &numdvd);
        counter = numdvd;
        while (counter != 0){
            int current;
            scanf("%d", &current);
            if (current == curnum){
                ++curnum;
            }
            --counter;
        }
        printf ("%d\n", numdvd - curnum+1);
        --numpass;
    }
    return 0;
}
