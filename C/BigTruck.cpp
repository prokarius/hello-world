#include<cstdio>
#include<queue>
#include<vector>
#include<functional>

#define INF 1<<30
#define MOD 20000
typedef std::pair<int, int> ii;

int items[101], visited[101], dist[101];
std::vector<ii> adjlist [101];

int main(){
    int i, n, m, a, b, d, target;
    ii x;

    // Read in the input
    scanf("%d", &n);
    for (i = 1; i<=n; ++i){
        scanf ("%d", &m);
        items[i] = -m;
        dist[i] = INF;
    }
    scanf ("%d", &m);
    while(m--){
        scanf("%d %d %d", &a, &b, &d);
        adjlist[a].push_back(ii(d*MOD, b));
        adjlist[b].push_back(ii(d*MOD, a));
    }

    // Set up and run Dijkstra without balls
    std::priority_queue <ii, std::vector<ii>, std::greater<ii>> heapq;
    heapq.push(ii(items[1],1));

    while (!heapq.empty()){
        int v = heapq.top().second;
        int w = heapq.top().first;
        heapq.pop();

        if (visited[v]) continue;
        ++visited[v];

        for (ii edge : adjlist[v]){
            int u = edge.second;
            int wnext = w + edge.first + items[u];
            if (dist[u] > wnext){
                dist[u] = wnext;
                heapq.push(ii(wnext, u));
            }
        }
    }

    // Check if it is even possible?
    if (dist[n] == INF){
        printf ("impossible\n");
        return 0;
    }
    printf ("%d %d\n", ((dist[n]-1)/MOD)+1, ((-dist[n])%MOD+MOD)%MOD);
    return 0;
}



