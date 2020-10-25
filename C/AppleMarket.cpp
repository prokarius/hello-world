// So here's the thing. E ~ 4*k + 4*r*c ~ 400k. V ~ k + 2*r*c ~ 100k
// So Dinic's should run in O(V2E) = 4E <-- exa = 10**15

// However, since the graph is more like a tree, the number of level graphs is
// limited by O(log(r)). i.e. Backflows will not be often found

// And during each level graph, we would probably saturate edges well, without
// needing to process O(VE) time.
// I.e. Probably O(1) BFS + DFS will do the trick per level graph, amortized.

// This means amortized, each level graph takes O(V+E) to process.
// So finally the time complexity will be O(V+E) * O(log(r)) ~ O(k * log(r))
// Yeah. Better use CPP instead of java though...

#include <bits/stdc++.h>

#define SMALL_INF 1<<30
#define INF 1LL<<50

struct FlowEdge{
    int start;
    int end;
    long long capacity;
    long long flow;
};

// Rip off my DinicSolver from AvoidApocalypse
class DinicSolver {
private:
    int n;
    std::vector<std::vector<int>> adjList;
    std::vector<FlowEdge> edgeList;
    std::vector<int> distance;
    std::vector<int> vertexIndex;

    // Returns true if there exists a level graph
    bool bfs(int source, int sink){
        std::queue<int> bfsQueue;

        // Reset the distances to INF.
        std::fill(distance.begin(), distance.end(), SMALL_INF);

        bfsQueue.push(source);
        distance[source] = 0;

        // Do BFS
        while (!bfsQueue.empty()){
            int curr = bfsQueue.front();
            bfsQueue.pop();

            if (curr == sink) return true;

            for (int neighbouringEdge : adjList[curr]){
                // If the edge is full, don't bother
                FlowEdge edge = edgeList[neighbouringEdge];
                if (edge.capacity - edge.flow == 0) continue;

                // If we have visited the node before don't bother
                int neighbour = edge.end;
                if (distance[neighbour] != SMALL_INF) continue;

                // Else, set the distance to the current distance +1
                distance[neighbour] = distance[curr] + 1;
                bfsQueue.push(neighbour);
            }
        }

        return false;
    }

    // Returns actual value of max flow.
    // Returns 0 if there is no such path in the level graph
    int dfs(int node, int sink, long long flow = INF){
        if (node == sink || flow == 0){
            return flow;
        }

        // Do DFS from the vertexIndex
        for (int &i = vertexIndex[node]; i < (int)adjList[node].size(); ++i){
            FlowEdge &edge = edgeList[adjList[node][i]];
            FlowEdge &otheredge = edgeList[adjList[node][i] ^ 1];

            // Check if the edge is not saturated
            if (edge.capacity - edge.flow == 0) continue;

            // Check if the edge is part of the level graph
            if (distance[edge.start] + 1 != distance[edge.end]) continue;

            // Do DFS
            long long currFlow = std::min(edge.capacity - edge.flow, flow);
            long long amountToPush = dfs(edge.end, sink, currFlow);

            if (amountToPush){
                edge.flow += amountToPush;
                otheredge.flow -= amountToPush;
                return amountToPush;
            }
        }

        // IF we are outside of the for loop, we have reached a ded end.
        // So we return 0.
        return 0;
    }

public:
    DinicSolver(int n) :
            n(n),
            adjList(n),
            distance(n),
            vertexIndex(n){
    }

    void addEdge(int start, int end, long long capacity){
        FlowEdge forwards = {start, end, capacity, 0};
        FlowEdge backwards = {end, start, 0, 0};
        edgeList.push_back(forwards);
        edgeList.push_back(backwards);

        adjList[start].push_back(edgeList.size()-2);
        adjList[end].push_back(edgeList.size()-1);
    }

    long long getMaxFlow(int source, int sink){

        long long out = 0;
        while (bfs(source, sink)){
            std::fill(vertexIndex.begin(), vertexIndex.end(), 0);
            while (long long flow = dfs(source, sink)){
                out += flow;
            }
        }
        return out;
    }
};

int nodeNum[64][64][6][6];
int numNodes = 1;

int main(){
    // Scan in input
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    // Set up the flow edges for the apple market.
    // Each of the nodes at [i][j] correspond to dx = 2**i, dy = 2**j
    // i.e. All rectangles with dimensions {1,2,4,8,16,32}x{1,2,4,8,16,32} are represented
    // e.g. nodeNum[i][j][0][0] represents the store at (i, j)
    // e.g. nodeNum[i][j][x][y] are the stores between (i, j) and (i+2**x, j+2**y)
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < m; ++c){
            for (int i = 0; i < 6; ++i){
                if (r + (1<<i) >= n + 1) break;
                for (int j = 0; j < 6; ++j){
                    if (c + (1<<j) >= m + 1) break;
                    nodeNum[r][c][i][j] = numNodes++;
                }
            }
        }
    }

    int SOURCE = 0;
    int SINK = k + numNodes + 1;

    // Total number of nodes = numQueries + number of nodes in the market + SOURCE + SINK
    DinicSolver dinicSolver(k + numNodes + 2);

    int start, end1, end2;
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < m; ++c){

            // Set up the 1x2**x nodes first.
            // Suppose we have a rectangle X at coordinate r, c. It has length 1x2**x.
            // Split X into two 1x(2**(x-1)) rectangles. Call the new rectangles A and B.
            // Then rectangle A corresponds to node[r][c][0][x-1]
            // And rectangle B corresponds to node[r][c+2**(r-1)][0][x-1]
            for (int i = 1; i < 6; ++i){
                if (c + (1<<i) >= m + 1) break;

                start = nodeNum[r][c][0][i];
                end1 = nodeNum[r][c][0][i-1];
                end2 = nodeNum[r][c+(1<<(i-1))][0][i-1];

                dinicSolver.addEdge(start, end1, INF);
                dinicSolver.addEdge(start, end2, INF);
            }

            // Now set up the 2**x x 2**y nodes.
            // Same as above. We split it into two new rectangles, and offset
            for (int i = 1; i < 6; ++i){
                if (r + (1<<i) >= n + 1) break;
                for (int j = 1; j < 6; ++j){
                    if (c + (1<<j) >= m + 1) break;

                    start = nodeNum[r][c][i][j];
                    end1 = nodeNum[r][c][i-1][j];
                    end2 = nodeNum[r+(1<<(i-1))][c][i-1][j];

                    dinicSolver.addEdge(start, end1, INF);
                    dinicSolver.addEdge(start, end2, INF);
                }
            }
        }
    }

    // Connect each output node to the sink
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            int apples;
            scanf("%d", &apples);

            int stallNum = nodeNum[i][j][0][0];
            dinicSolver.addEdge(stallNum, SINK, apples);
        }
    }

    // Scan in each query
    for (int i = 0; i < k; ++i){
        int x1, y1, x2, y2, money;
        scanf("%d %d %d %d %d", &x1, &x2, &y1, &y2, &money);
        --x1; --x2; --y1; --y2;

        // So if I want to cover this area of size (6 x 13):
        // ...................
        // ..xxxxxxxxxxxxx....
        // ..xxxxxxxxxxxxx....
        // ..xxxxxxxxxxxxx....
        // ..xxxxxxxxxxxxx....
        // ..xxxxxxxxxxxxx....
        // ..xxxxxxxxxxxxx....
        // ...................
        //
        // I can just cover it with the following 4 (4 x 8) rectangles:
        // ...................
        // ..A----B-A----B....
        // ..|xxxx|x|xxxx|....
        // ..C----D-C----D....
        // ..A----B-A----B....
        // ..|xxxx|x|xxxx|....
        // ..C----D-C----D....
        // ...................

        int dx = x2-x1+1;
        int dy = y2-y1+1;

        // Get the largest rectangle size:
        int sizeX = 31 - __builtin_clz(dx);
        int sizeY = 31 - __builtin_clz(dy);

        // Set up the flow for the 4 rectangles
        int topLeftA = nodeNum[x1][y1][sizeX][sizeY];
        int topLeftB = nodeNum[x2 - (1<<sizeX) + 1][y1][sizeX][sizeY];
        int topLeftC = nodeNum[x1][y2 - (1<<sizeY) + 1][sizeX][sizeY];
        int topLeftD = nodeNum[x2 - (1<<sizeX) + 1][y2 - (1<<sizeY) + 1][sizeX][sizeY];

        int customerNode = numNodes + i;

        dinicSolver.addEdge(customerNode, topLeftA, INF);
        dinicSolver.addEdge(customerNode, topLeftB, INF);
        dinicSolver.addEdge(customerNode, topLeftC, INF);
        dinicSolver.addEdge(customerNode, topLeftD, INF);

        // And don't forget to add an edge from source to the customerNode
        dinicSolver.addEdge(SOURCE, customerNode, money);
    }

    // Run maxflow and print the output
    printf("%lld\n", dinicSolver.getMaxFlow(SOURCE, SINK));

    return 0;
}

