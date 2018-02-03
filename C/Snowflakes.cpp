#include<cstdio>
#include<unordered_set>

#define MAX(x,y) (x>y)?(x):(y)

int main(){
    int arr[1000005];
    int i, T, n, ph, start, end, best;
    scanf("%d", &T);
    while (T--){
        std::unordered_set<int> a;
        start=0, end=0, best=0;
        scanf("%d", &n);
        for (i=0; i<n; i++){
            scanf("%d", &ph);
            arr[i] = ph;
        }
        while (start < n){
            if (a.find(arr[start]) == a.end()) a.insert(arr[start++]);
            else {
                best = MAX(best, a.size());
                while (arr[end] != arr[start]) a.erase(arr[end++]);
                start++;
                end++;
            }
        }
        best = MAX(best, a.size());
        printf ("%d\n", best);
    }
}
