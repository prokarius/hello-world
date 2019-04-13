#include<stdio.h>

int max(int x, int y){
    if (x>y){
        return x;
    }
    return y;
}

int main(){
    int trains[2001];
    int len[2001][2];
    int numtrains;
    scanf("%d", &numtrains);
    for (int i=0; i<numtrains; ++i){
        scanf("%d", &trains[i]);
    }

    // Stupid case, when nuntrajns is 0, we should print 0 instead of -1
    if (numtrains == 0){
        printf("0\n");
        return 0;
    }

    // We need to find the longest in/decreasing subsequence that starts from
    // a given train. the sum of the length of these 2 is the answer.
    // dp from the back!
    // Initialise the last cell
    len[numtrains-1][0] = 1;
    len[numtrains-1][1] = 1;
    for (int i=numtrains-2; i>=0; --i){
        int numbest = 0;
        int numworst = 0;
        for (int j=i+1; j<numtrains; ++j){
            if (trains[i] > trains[j]){
                numbest = max(numbest, len[j][0]);
            }
            if (trains[i] < trains[j]){
                numworst = max(numworst, len[j][1]);
            }
        }

        // Then store the dp
        len[i][0] = numbest +1;
        len[i][1] = numworst +1;
    }

    // Loop through the entire array and find the best.
    int best = 0;
    for (int i=0; i<numtrains; ++i){
        best = max(best, len[i][0] + len[i][1]);
    }

    printf("%d\n", best-1);

    return 0;
}
