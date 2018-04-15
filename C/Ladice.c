#include<stdio.h>

// Onion methods
int Onion[300005];
int dead[300005];

void init(int n){
    for (int i=0; i<n; ++i){
        Onion[i] = i;
    }
}

int find(int v){
    if (Onion[v] != v){
        Onion[v] = find(Onion[v]);
    }
    return Onion[v];
}

// Note that each time you onion two components, you are essentially merging
// them into one bigger component.
// If you try to merge two of the larger components, you essentially cause
// a cycle, and this will force everyone into their own slots.
// We will use this to determine whether it's SMECE or LADICA
void onion(int a, int b){
    int x = find(a);
    int y = find(b);

    // If the two components are dead already, then don't even bother.
    if (dead[x] && dead[y]){
        printf("SMECE\n");
        return;
    }

    // Else, you can still merge them. So print out LADICA.
    printf("LADICA\n");

    // Now, if they belong to the same component. then kill the component.
    // All the items in the component are now dead
    // (i.e. they are in their own drawers now)
    if (x == y){
        dead[x] = 1;
        return;
    }

    // Else they are in different components. Onion them!
    Onion[x] = y;

    // Lastly, check of either the two components are dead.
    // If they are, then that will cause the other to be dead as well.
    if (dead[x] || dead[y]){
        dead[x] = 1;
        dead[y] = 1;
    }
}

int main(){
    int Q, N;
    scanf("%d %d", &Q, &N);
    init(N+1);
    for (int i=0; i<Q; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        onion(a, b);
    }
    return 0;
}
