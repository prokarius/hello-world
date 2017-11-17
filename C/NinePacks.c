#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

int doglist[1005], bunlist[1005];

int main(){
    int K, C, i, j, sumdog=0, sumbun=0;
    int dog[1005], bun[1005], doglist[100005], bunlist[100005];

    for (i=0; i<100002; ++i){
        doglist[i] = bunlist[i] = 10000;
    }

    scanf("%d", &K);
    i = K;
    while (i--){
        scanf("%d", &C);
        dog[i] = C;
        sumdog += C;
    }
    while(++i < K){
        for (j = 0; j<sumdog; ++j){
            if (doglist[sumdog-j] != 10000){
                if (doglist[dog[i]+sumdog-j] > doglist[sumdog - j] + 1){
                    doglist[dog[i]+sumdog-j] = doglist[sumdog - j] + 1;
                }
            }
        }
        doglist[dog[i]] = 1;
    }

    scanf("%d", &K);
    i = K;
    while (i--){
        scanf("%d", &C);
        bun[i] = C;
        sumbun += C;
    }
    while(++i < K){
        for (j = 0; j<sumbun; ++j){
            if (bunlist[sumbun-j] != 10000){
                if (bunlist[bun[i]+sumbun-j] > bunlist[sumbun - j] + 1){
                    bunlist[bun[i]+sumbun-j] = bunlist[sumbun - j] + 1;
                }
            }
        }
        bunlist[bun[i]] = 1;
    }

    int o = 100000;
    for (i=0; i<=(MIN(sumdog, sumbun)); ++i){
        if (bunlist[i] < 10000 && doglist[i] < 10000){
            int check = bunlist[i] + doglist[i];
            o = MIN(check, o);
        }
    }
    if (o != 100000) printf ("%d", o);
    else printf ("impossible");
    return 0;
}
