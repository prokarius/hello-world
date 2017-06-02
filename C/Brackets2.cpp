#include <cstdio>

int alist [5005];
int maxinrange [5005][5005], mininrange[5005][5005];

int main() {
    int score = 0, n = 0;
    alist[0] = 0;
    char ch;
    while (scanf("%c ", &ch) != EOF){
        if (ch == '('){
            score += 1;
            n++;
        }
        else if (ch == ')'){
            score -= 1;
            n++;
        }
        alist[n] = score;
    }
    alist [n+1] = score;

    if (n%2 == 1){
        printf ("impossible");
        return 0;
    }

    for (int i = 0; i <= n+1 ; i++){
        maxinrange[i][i] = alist[i];
        mininrange[i][i] = alist[i];
        for (int j = i+1; j <= n+1; j++){
            if (maxinrange [i][j-1] > alist[j]){
                maxinrange [i][j] = maxinrange [i][j-1];
            }
            else {
                maxinrange [i][j] = alist[j];
            }
            if (mininrange [i][j-1] < alist[j]){
                mininrange [i][j] = mininrange [i][j-1];
            }
            else {
                mininrange [i][j] = alist[j];
            }
        }
    }

    for (int i = 1; i <= n ; i++){
        if (mininrange[0][i-1] >= 0){
            int curscore = 2*alist[i-1];
            for (int j = i; j <= n; j++){
                int tscore = curscore - maxinrange[i][j];
                if (tscore >= 0){
                    int sscore = curscore - alist[j];
                    if (j == n){
                        if (sscore == 0){
                            printf ("possible");
                            return 0;
                        }
                    }
                    else{
                        sscore -= alist[j];
                        int rscore = sscore + mininrange[j+1][n];
                        if (rscore >= 0){
                            sscore += (alist[n]);
                            if (sscore == 0){
                                printf ("possible");
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    if ((mininrange [0][n-1] >= 0) && (score == 0)){
        printf("possible");
        return 0;
    }
    printf ("impossible");
    return 0;
}
