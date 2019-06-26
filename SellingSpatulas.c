#include<stdio.h>

typedef struct {
    int minutes;
    int profit;
} Sale;

Sale sale(int minutes, int profit){
    Sale out;
    out.minutes = minutes;
    out.profit = profit;
    return out;
}

Sale sales[1024];

int solve(int n){
    // Scan in input
    for (int i = 0; i < n; ++i){
        int mins, dollar, cents;
        scanf("%d %d.%d", &mins, &dollar, &cents);
        sales[i] = sale(mins, dollar*100 + cents);
    }

        // Use


}

int main(){
    int n;
    scanf("%d", &n);
    while (n != 0){
        solve(n);
        scanf("%d". &n);
    }
}
