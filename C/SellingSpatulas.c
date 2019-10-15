#include<stdio.h>

int time[1024];
int profit[1024];
int prefixSum[1024];

char dollarChars[8];
char timeChars[8];

void solve(int n){
    // Scan in input
    for (int i = 0; i < n; ++i){
        // Scan in the time
        // Wow I didn't know this was such a pain
        char timeChar;
        scanf("%c", &timeChar);

        for (int i = 0; i < 8; ++i){
            timeChars[i] = timeChar;
            if (timeChar == ' ') break;
            scanf("%c", &timeChar);
        }

        int times = 0;
        int startChar = 1;
        while(timeChars[startChar] != ' '){
            times = times * 10 + timeChars[startChar] - '0';
            startChar++;
        }
        time[i] = times;

        // Scan in the dollar amount
        // What a pain.
        char dollarChar;
        scanf("%c", &dollarChar);

        for (int i = 0; i < 8; ++i){
            dollarChars[i] = dollarChar;
            if (dollarChar == '.') break;
            scanf("%c", &dollarChar);
        }

        int dollars = 0;
        startChar = 0;
        if (dollarChars[0] == '-') startChar++;
        while(dollarChars[startChar] != '.'){
            dollars = dollars * 10 + dollarChars[startChar] - '0';
            startChar++;
        }
        if (dollarChars[0] == '-') dollars *= -1;

        int cents;
        scanf("%d", &cents);
        profit[i] = (dollars*100) + cents*((dollarChars[0] == '-')?(-1):(1));
    }

    // Calculate prefixSum
    prefixSum[0] = 0;
    for (int i = 0; i < n; ++i){
        prefixSum[i+1] = prefixSum[i] + profit[i];
    }

    // Bruteforce
    int best = 0;
    int bestStart = -1;
    int bestEnd = -1;
    int bestLength = -1;
    for (int i = 0; i < n; ++i){
        for (int j = i; j < n; ++j){
            // Here, we open from time i to time j inclusive
            int dt = (time[j] - time[i])+ 1;
            int profits = (prefixSum[j+1] - prefixSum[i]) - dt*8;

            if (profits > best || (profits == best && dt < bestLength)){
                best = profits;
                bestStart = time[i];
                bestEnd = time[j];
                bestLength = dt;
            }
        }
    }

    // Do we have profits?
    if (best == 0){
        printf("no profit\n");
        return;
    }

    printf("%d.%02d %d %d\n", best / 100, best % 100, bestStart, bestEnd);
}

int main(){
    int n;
    scanf("%d", &n);

    while (n){
        solve(n);
        scanf("%d", &n);
    }

    return 0;
}

