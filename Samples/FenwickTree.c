#include<stdio.h>
#define MAXN 5000001

long long fenwicktree[MAXN];

int LSOne(int i){
    return i&(-i);
}

void update(int v, long long add){
    while (v < MAXN){
        fenwicktree[v] += add;
        v += LSOne(v);
    }
}

// Returns the range query minimum
long long __rsq(int end){
    long long sum = 0;
    while (end > 0){
        sum += fenwicktree[end];
        end -= LSOne (end);
    }
    return sum;
}

long long rsq(int start, int end){
    return __rsq(end) - __rsq(start-1);
}
