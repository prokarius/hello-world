#include<cstdio>
#include<queue>
#include<vector>
#include<functional>

#define INF 1<<30
typedef std::pair<int, int> ii;

int visited[10005], dist[10005];
std::vector <ii> adjlist[10005];

int main(){
    int i, n, m, q, s, a, b, w;
    ii x;
    scanf ("%d %d %d %d", &n, &m, &q, &s);
    while (n){
        // Scan in the adjlists.
        while (m--){
            scanf ("%d %d %d", &a, &b, &w);
            x.first = b;
            x.second = w;
            adjlist[a].push_back(x);
        }

        // Set all the distance estimates to INF except source node.
        for (i = 0; i<n; i++) dist[i] = INF;
        dist[s] = 0;
        std::priority_queue <ii, std::vector<ii>, std::greater<ii>> heapq;

        heapq.push(ii(0, s));

        // Run Dijkstra forever.
        while (!heapq.empty()){
            int v = heapq.top().second;
            int w = heapq.top().first;
            heapq.pop();
            if (visited[v]) continue;
            else ++visited[v];

            for (ii edge : adjlist[v]){
                int u = edge.first;
                int w_next = w + edge.second;
                if (dist[u] > w_next){
                    dist[u] = w_next;
                    heapq.push(ii(w_next, u));
                }
            }
        }

        while (q--){
            scanf("%d", &b);
            if (dist[b] != 1<<30) printf("%d\n", dist[b]);
            else printf ("Impossible\n");
        }

        // Reset the stuff
        for (i=0; i<n; ++i){
            adjlist[i].clear();
            visited[i] = 0;
        }
        printf ("\n");
        scanf ("%d %d %d %d", &n, &m, &q, &s);
    }
    return 0;
}
