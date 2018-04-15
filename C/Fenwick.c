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
long long rsq(int end){
    long long sum = 0;
    while (end > 0){
        sum += fenwicktree[end];
        end -= LSOne (end);
    }
    return sum;
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i=0; i<q; ++i){
        char ph;
        scanf(" %c", &ph);
        if (ph == '+'){
            int index, updateValue;
            scanf("%d %d", &index, &updateValue);
            update(index+1, updateValue);
        }
        else {
            int end;
            scanf("%d", &end);
            printf("%lld\n", rsq(end));
        }
    }
    return 0;
}

