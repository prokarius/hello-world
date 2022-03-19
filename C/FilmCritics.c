#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int score;
    int num;
} Critic;

Critic critic(int score, int num){
    Critic new;
    new.score = score;
    new.num = num;
    return new;
}

Critic critics[200005];
int out[200005];

int cmpfunc(const void* a, const void* b){
    return (*(Critic*)a).score - (*(Critic*)b).score;
}

int main(){
    // Scan in input
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    // Guard, is the average even possible...?
    if (k % m != 0){
        printf("impossible\n");
        return 0;
    }

    // Guard, Susan wants it to score 0
    if (k == 0){
        printf("impossible\n");
        return 0;
    }

    for (int i = 0; i < n; ++i){
        int score;
        scanf("%d", &score);
        critics[i] = critic(score, i+1);
    }

    // The critics that will give 0 comes from those with low opinions.
    // We can ensure they give 0 by choosing them in reverse order of opinion
    // Sort the critics
    qsort(critics, n, sizeof(Critic), cmpfunc);
    int hiNum = n - k / m;  // Select k/m good reviews.
    int loNum = hiNum - 1;  // Number of 0s
    
    // The first person will just give m, so add them to out
    out[0] = critics[hiNum].num;
    hiNum++;
    int count = 1;

    for (int i = 1; i < n; ++i){
        int currScore = m * count;

        // Should we ask the next critic to give 0 score review?
        if (loNum >= 0 && currScore > critics[loNum].score * i){
            out[i] = critics[loNum].num;
            loNum--;
            continue;
        }
        // Or should we ask the next critic to give a m score review?
        else if (hiNum < n && currScore <= critics[hiNum].score * i){
            out[i] = critics[hiNum].num;
            hiNum++;
            count++;
            continue;
        }

        // We ran out of critics to invite to improve / deprove our score...
        else {
            printf("impossible\n");
            return 0;
        }
    }

    // Print the output if we can make it...
    for (int i = 0; i < n; ++i){
        printf("%d ", out[i]);
    }
    printf("\n"); 

    return 0;
}

