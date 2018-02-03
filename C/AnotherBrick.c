#include <stdio.h>

int main(){
    int h, w, n;
    scanf ("%d %d %d", &h, &w, &n);
    while (h != 0){
        int curr = w;
        while (curr != 0){
            int brick;
            if (scanf ("%d", &brick) == EOF){
                printf ("NO");
                return 0;
            }
            if (curr < brick){
                printf ("NO");
                return 0;
            }
            curr -= brick;
        }
        h -= 1;
    }
    printf ("YES");
    return 0;
}
