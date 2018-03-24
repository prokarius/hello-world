#include<cstdio>

// Hi, I happened to see this problem on the front page of code crunch
// I guess it'll be fun to give this problem a shot
// I mean, this isn't any different from 2040, except it's not Java and my WAs
// wont be penalised as harshly! :)
// ... right...? :|

int array[105][105][105];
int sum[102][102][102];

int sum(int i, int j, int k){
    // We will use the power of inclusion exclusion.
    // See, remember the sum of the array
    return sum[i][j][k] -

int main(){
    long long best = -1;
    int i, j;
    int n;

    // Scan in input into array[depth][row][col] in that order.
    scanf ("%d", &n);
    for (i=0; i<n*n; ++i){
        for (j=0; j<n*n; ++j){
            scanf("%d", array[i][j/n][j%n]);
        }
    }

    // Notice that if we can calculate volume sum in O(1) time, we can use Kanade's
    // in 1 dimension, and bruteforce in the other two dimensions to figure out
    // the best possible distance! This takes O(1) x O(n) x O(n2) x O(n2) = O(n5)

    for (i=0; i<n; ++i){
        for (j=0; j<n; ++j){
            sum = 


    printf ("%lld\n", best);
}
