#include<cstdio>
#include<vector>

void solve(){
    // Scan in input
    int n;
    long long a, b, c, x, y;
    scanf("%d %lld %lld %lld %lld %lld", &n, &a, &b, &c, &x, &y);

    // Generate all the numbers
    std::vector<int> lst;
    long long curr = a;
    lst.push_back(a);
    for (int i = 1; i < n; ++i){
        curr = (curr * b + a) % c;
        lst.push_back(curr);
    }

    // Radix sort the numbers
    std::vector<int> sorted[1<<8];
    for (int i = 0; i < 32; i+=8){ 
        // Clear the buckets
        for (int j = 0; j < 256; ++j){
            sorted[j].clear();
        }

        // Populate the buckets
        for(int j : lst){
            sorted[(j >> i) & 255].push_back(j);
        }

        // Clear the original list
        lst.clear();

        // Populate the list
        for (int j = 0; j < 256; ++j){
            for(int k : sorted[j]){
                lst.push_back(k);
            }
        }
    }

    // Get the hash
    long long v = 0;
    for (int curr : lst) v = (v * x + curr) % y;
    printf("%d\n", (int) v);
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    
    for (int i = 0; i < testcases; ++i) solve();
    return 0;
}

