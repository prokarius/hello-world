#include <stdio.h>

int main(){
    int numtest;
    scanf("%d", &numtest);
    while (numtest--){
        int q, i=0, inputlist[100005], rev = 0, delf = 0, delb = 0, ph = 0;
        char R[100005], nowa;
        scanf ("%s %d ", R, &q);
        scanf ("%c", &nowa);
        scanf ("%c", &nowa);
        while (nowa != ']'){
            if (nowa == ','){
                inputlist[i++] = ph;
                ph = 0;
            }
            else{
                ph = 10*ph + nowa -'0';
            }
            scanf ("%c", &nowa);
        }
        inputlist[i] = ph;
        i = 0;
        while (R[i]!='\0'){
            if (R[i++] == 'D'){
                if (rev % 2 == 1){
                    delb += 1;
                }
                else {
                    delf += 1;
                }
            }
            else{
                rev += 1;
            }
        }
        if (delb + delf > q){
            printf ("error\n");
            continue;
        }
        else if (delb + delf == q){
            printf ("[]\n");
            continue;
        }
        printf ("[");
        if (rev %2 ==0){
            for (i = delf; i < (q-delb-1); i++){
                printf ("%d,", inputlist[i]);
            }
            printf ("%d", inputlist[i]);
        }
        else {
            for (i = q-delb-1; i > delf; i--){
                printf ("%d,", inputlist[i]);
            }
            printf ("%d", inputlist[i]);
        }
        printf("]\n");
    }
    return 0;
}
