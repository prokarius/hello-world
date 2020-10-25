#include<cstdio>
#include<unordered_set>
#include<unordered_map>

#define MIN(x, y) (x<y)?(x):(y)
#define MAX(x, y) (x>y)?(x):(y)

int a[1<<20];
int left[1<<20];
int right[1<<20];
int primes[10000007];

std::unordered_set<int> factors[1<<20];

void genPrimes(){
    for (int i = 0; i < 10000003; ++i){
        primes[i] = i;
    }

    for (int i = 2; i*i <= 100000003 ; ++i){
        if (primes[i] != i) continue;
        for (int j = i*i; j < 10000003; j += i){
            if (primes[j] == j) primes[j] = i;
        }
    }
}

std::unordered_set<int> getFactors(int a){
    std::unordered_set<int> out;
    while (a != 1){
        int factor = primes[a];
        out.insert(factor);
        a /= factor;
    }
    return out;
}

int out[1<<20];

int recurse(int lo, int hi, int parent){
    if (lo > hi) return 1;
    if (lo == hi){
        out[lo] = parent;
        return 1;
    }
    for (int i = lo, j = hi; i <= j; ++i, --j){
        if (left[i] < lo && right[i] > hi){
            out[i] = parent;
            return recurse(lo, i-1, i) && recurse(i+1, hi, i);
        }
        if (left[j] < lo && right[j] > hi){
            out[j] = parent;
            return recurse(lo, j-1, j) && recurse(j+1, hi, j);
        }
    }

    return 0;
}

int main(){
    genPrimes();

    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &a[i]);
        factors[i] = getFactors(a[i]);
    }

    // Process factors from the left
    std::unordered_map<int, int> curr;
    for (int i = 0; i < n; ++i){
        int index = i + 1;
        for (int factor : factors[i]){
            if (curr.find(factor) != curr.end()){
                left[index] = MAX(left[index], curr[factor]);
            }
            curr[factor] = index;
        }
    }
    
    // And from the right
    curr.clear();
    for (int i = 0; i <= n+1; ++i) right[i] = n+1;

    for (int i = n-1; i >= 0; --i){
        int index = i + 1;
        for (int factor : factors[i]){
            if (curr.find(factor) != curr.end()){
                right[index] = MIN(right[index], curr[factor]);
            }
            curr[factor] = index;
        }
    }

    if (recurse(1, n, 0)){
        for (int i = 1; i <= n; ++i){
            printf("%d ", out[i]);
        }
        printf("\n");
    }
    else {
        printf("impossible\n");
    }

    return 0;
}

