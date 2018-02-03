#include<cstdio>
#include<queue>
#include<vector>
#include<functional>

#define INF 1<<30
typedef std::pair<int, int> ii;

int dr[5] = {0, 1, 0, -1, 0};
int grid[2505], visited[2505], dist[2505];

int main(){
    char ph;
    int i, j, r, c, k, start, end;

    // Scan in input
    scanf ("%d %d %d ", &r, &c, &k);
    for (i=0; i<r; ++i){
        for (j=0; j<c; ++j){
            scanf(" %c", &ph);
            if (ph == '#') grid[i*c + j] = -1;
            else if (ph == 'M') grid[i*c + j] = 3;
            else if (ph == 'F') grid[i*c + j] = 2;
            else if (ph == '.') grid[i*c + j] = 1;
            else if (ph == 'S'){
                start = i*c + j;
                grid[i*c + j] = 1;
            }
            else if (ph == 'G'){
                end = i*c + j;
                grid[i*c + j] = 1;
            }
        }
    }

    for (i=0; i<r*c; ++i) dist[i] = INF;

    // We will be doing a dijkstra, where the keys is the current node, the
    // value is number of days * 1000 + (K - stamina)
    int v, w, currr, currc, nextr, nextc, nextv, nextw, stamina;
    std::priority_queue <ii, std::vector<ii>, std::greater<ii> > heapq;
    heapq.push(ii(0, start));

    while (!heapq.empty()){
        v = heapq.top().second;
        w = heapq.top().first;
        heapq.pop();
        if (visited[v]) continue;
        ++visited[v];
        currr = v/c;
        currc = v%c;
        stamina = w % 1000;
        for (i = 0; i<4; ++i){
            nextr = currr + dr[i];
            nextc = currc + dr[i+1];
            nextv = nextr * c + nextc;

            // Out of bounds?
            if (nextr < 0 || nextr >= r || nextc < 0 || nextc >= c) continue;

            // The grid doesn't allow us to move at all?
            if (grid[nextv] > k || grid[nextv] == -1) continue;

            // If we are out of stamina for the day, make it a new day.
            if (stamina + grid[nextv] > k){
                nextw = (1 + w/1000)*1000 + grid[nextv];
            }
            else {
                nextw = w + grid[nextv];
            }

            if (dist[nextv] <= nextw) continue;
            dist[nextv] = nextw;

            // If we are out of stamina, increase the day by 1 and subtract.
            heapq.push(ii(nextw, nextv));
        }
    }

    if (dist[end] == INF) printf ("-1\n");
    else printf ("%d\n", (dist[end]/1000)+1);

    return 0;
}
