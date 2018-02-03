#include<stdio.h>

int N, onion[200005], numonion[100005];
long long sum[100005];

int find(int n){
    // Returns the parent of the given integer. This number is bigger than N.
    if (onion[n] == n && onion[n] > N) return onion[n];
    else{
        onion[n] = find(onion[n]);
        return onion[n];
    }
}

void oniononion (int p, int q){
    // Onions the set p and q
    // Finds the parent of p and q, and onions them if different
    // Same time, adds the sum of p to the sum of q
    // And add the number of elements of p to q too
    int parp = find(p), parq = find(q);
    if (onion[parp] != onion[parq]){
        onion[parp] = onion[parq];
        sum[parq-N] += sum[parp-N];
        numonion[parq-N] += numonion[parp-N];
    }
}

void moveonion (int p, int q){
    // Move p into the set of q
    // Don't forget to change the sums and the nums.
    int parp = find(p), parq = find(q);
    onion[p] = parq;
    sum[parp-N] -= p;
    sum[parq-N] += p;
    --numonion[parp-N];
    ++numonion[parq-N];
}

void print (int p){
    // Pretty prints the output
    int parp = find(p);
    printf ("%d %lld\n", numonion[parp-N], sum[parp-N]);
}

void cod(int M){
    int i, type, p, q;

    // Reset our onion
    for (i = 0; i<=N; ++i){
        onion[i] = i+N;
        sum[i] = i;
        numonion[i] = 1;
    }
    for (i = N+1; i<=2*N; ++i) onion[i] = i;

    while (M--){
        // Scan in our inputs and work them!
        scanf("%d", &type);

        // This is the onion operation
        if (type == 1){
            scanf ("%d %d", &p, &q);
            oniononion(p,q);
        }

        // This is the move operation
        else if (type == 2){
            scanf ("%d %d", &p, &q);
            moveonion(p,q);
        }

        // This is the print operation
        else {
            scanf ("%d", &p);
            print (p);
        }
    }
}

// Question: When will moveonion p and q be slow?
// Answer: When p is the parent of everyone
// Solution: Don't make any element be a parent.
// All elements are free to move around, since they each then have a parent
// Think of the parent as a sort of each element's parent set.

int main (){
    // This is here for the main test cases loop
    int M;
    while (scanf("%d %d", &N, &M) != EOF) cod(M);
    return 0;
}
