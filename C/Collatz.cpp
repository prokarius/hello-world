#include<cstdio>
#include<set>

long long gcd (long long a, long long b){
    if (b) return gcd (b, a%b);
    else return a;
}

int main(){
    std::set <long long> ans, myset[2];
    int n, i=-1;
    long long ph, k;
    scanf ("%d", &n);
    while (++i < n){
        scanf ("%lld", &ph);
        for (long long j: myset[i%2]){
            k = gcd(j, ph);
            myset[(i+1)%2].insert(k);
            ans.insert(k);
        }
        myset[(i+1)%2].insert(ph);
        ans.insert(ph);
        myset[i%2].clear();
    }
    printf ("%lu\n", ans.size());
    return 0;
}
