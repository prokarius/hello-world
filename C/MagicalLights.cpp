#include<cstdio>
#include<vector>

int n, q;
int color[300005];
std::vector<int> adjList[300005];

typedef struct {
    int start;
    int end;
} Node;

Node nodes[300005];  // To store where to where is the query from
int index = 0;  // This will be the new index number

// DFS to figure out the new ordering of the tree, essentially flattening it.
// This will map queries to the fenwick tree
void dfs(int x){
    index++;
    nodes[x].start = index;

    for (int neighbor : adjList[x]){
        dfs(neighbor);
    }

    nodes[x].end = index;
}

// Fenwick trees here
int fenwicks[4][300005];
int LSOne(int x){
    return x&-x;
}

void update(int node, int color){
    int treeNum = color / 25;
    int delta = 1 << (color % 25);
    for (int i = node; i <= n; i += LSOne(i)){
        fenwicks[treeNum][i] ^= delta;
    }
}

// Range XOR Query
int _RXQ(int node, int treeNum){
    int out = 0;
    for (int i = node; i >= 1; i -= LSOne(i)){
        out ^= fenwicks[treeNum][i];
    }
    return out;
}

int RXQ(int node){
    int out = 0;
    for (int i = 0; i < 4; ++i){
        out += __builtin_popcount(_RXQ(nodes[node].end, i) ^ _RXQ(nodes[node].start - 1, i));
    }
    return out;
}

int main(){
    // Scan in input
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; ++i){
        scanf("%d", &color[i]);
        color[i]--;
    }

    for (int i = 2; i <= n; ++i){
        int parent;
        scanf("%d", &parent);
        adjList[parent].push_back(i);
    }

    // Do DFS to figure out what queries would be later
    // Also initialize the colors in the fenwick trees now
    dfs(1);
    for (int i = 1; i <= n; ++i){
        update(nodes[i].start, color[i]);
    }

    // Process the queries
    for (int i = 0; i < q; ++i){
        int k, x;
        scanf("%d %d", &k, &x);

        // Query the number of magical lights
        if (k == 0){
            printf("%d\n", RXQ(x));
            continue;
        }

        // Else update the color of the trees
        k--;
        update(nodes[x].start, color[x]);
        color[x] = k;
        update(nodes[x].start, k);
    }
}

