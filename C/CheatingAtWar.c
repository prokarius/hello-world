#include<stdio.h>

int n = 26;

int mapping[256];
int matrix[27][27];

// Matthew's code copy pasta
int hungarian() {
    int u[n+1], v[n+1], p[n+1], way[n+1];
    for (int i = 0; i <= n; ++i){
        u[i] = v[i] = p[i] = way[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        int minv[n+1];
        int used[n+1];

        for (int i = 0; i < n+1; ++i){
            minv[i] = 1<<30;
            used[i] = 0;
        }

        do {
            used[j0] = 1;
            int i0 = p[j0], delta = 1<<30,  j1;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    int cur = matrix[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0;j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;  v[j] -= delta;
                } else
                    minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    return v[0]; //negated min cost ~= max cost
}

void solve(){
    // Scan in input
    int yraglac[32], opponent[32];

    for (int i = 1; i <= n; ++i){
        char chr;
        scanf(" %c", &chr);
        yraglac[i] = mapping[chr];
    }

    for (int i = 1; i <= n; ++i){
        char chr;
        scanf(" %c", &chr);
        opponent[i] = mapping[chr];
    }

    // Construct the matrix
    // matrix[i][j] is 2 if yraglac[i] > opponent[j]
    // matrix[i][j] is 1 if yraglac[i] == opponent[j]
    // matrix[i][j] is 0 if yraglac[i] < opponent[j]

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            if (yraglac[i] > opponent[j]) matrix[i][j] = 2;
            else if (yraglac[i] == opponent[j]) matrix[i][j] = 1;
            else matrix[i][j] = 0;
        }
    }

    // Then do Hungarian Algo on it. Ans = 52 - mincost.
    printf("%d\n", 52+hungarian());
}

int main(){
    // Set up the mapping
    for (char i = '2'; i <= '9'; ++i) mapping[i] = i - '0';
    mapping['T'] = 10;
    mapping['J'] = 11;
    mapping['Q'] = 12;
    mapping['K'] = 13;
    mapping['A'] = 14;

    int testcases;
    scanf("%d", &testcases);

    while(testcases--) solve();
    return 0;
}

