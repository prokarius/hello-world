#include<stdio.h>

long long array[1<<20];

// Ugh, global variables because binsearch needs access to n...
long long n, m, a, c, x0;

// Returns 1 if we found it!
int binsearch(long long val){
    int lo = 0;
    int hi = n-1;

    while(lo <= hi){
        int mid = (lo+hi)/2;
        if (array[mid] == val) return 1;
        else if (array[mid] < val) lo = mid+1;
        else hi = mid-1;
    }

    // Ain't found it
    return 0;
}

int main(){
    // Scan in input
    scanf("%lld %lld %lld %lld %lld", &n, &m, &a, &c, &x0); 

    array[0] = x0;
    for (int i = 0; i < n; ++i){
        array[i] = (x0*a + c) % m;
        x0 = array[i];
    }

    // Actually, wouldn't just simulating this shit be fast enough...?
    int out = 0;
    for (int i = 0; i < n; ++i){
        out += binsearch(array[i]);
    }

    printf("%d\n", out);

    return 0;
}
