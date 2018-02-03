int onion[100005];

int find(int n){
    // Returns the parent
    if (onion[n] == n){
        return n;
    }
    // Else do some path compression shit
    else{
        onion[n] = find(onion[n]);
        return onion[n];
    }
}

// Set up the onion
int i, N=100005;
for (i=0; i<N; ++i){
    onion[i] = i;
}
