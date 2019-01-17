#include <bits/stdc++.h>

#define INF 1<<30

struct FlowEdge{
    int start;
    int end;
    int capacity;
    int flow;
};

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
        std::fill(distance.begin(), distance.end(), INF);

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
                if (distance[neighbour] != INF) continue;

                // Else, set the distance to the current distance +1
                distance[neighbour] = distance[curr] + 1;
                bfsQueue.push(neighbour);
            }
        }

        return false;
    }

    // Returns actual value of max flow.
    // Returns 0 if there is no such path in the level graph
    int dfs(int node, int sink, int flow = INF){
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
            int currFlow = std::min(edge.capacity - edge.flow, flow);
            int amountToPush = dfs(edge.end, sink, currFlow);

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

    void addEdge(int start, int end, int capacity){
        FlowEdge forwards = {start, end, capacity, 0};
        FlowEdge backwards = {end, start, 0, 0};
        edgeList.push_back(forwards);
        edgeList.push_back(backwards);

        adjList[start].push_back(edgeList.size()-2);
        adjList[end].push_back(edgeList.size()-1);
    }

    int getMaxFlow(int source, int sink){
        int out = 0;
        while (bfs(source, sink)){
            std::fill(vertexIndex.begin(), vertexIndex.end(), 0);
            while (int flow = dfs(source, sink)){
                out += flow;
            }
        }
        return out;
    }
};

void run(){
    // Scan in input
    int n;
    scanf("%d", &n);

    int startingNode, groupSize, timeSteps;
    scanf("%d %d %d", &startingNode, &groupSize, &timeSteps);

    --startingNode;
    ++timeSteps;

    int medical;
    scanf("%d", &medical);

    std::vector<int> safehouses;
    for (int i = 0; i < medical; ++i){
        int safehouse;
        scanf("%d", &safehouse);
        --safehouse;
        safehouses.push_back(safehouse);
    }

    int numVertices = n * timeSteps + 2;
    DinicSolver dinicSolver(numVertices);

    int edges;
    scanf("%d", &edges);

    for (int i = 0; i < edges; ++i){
        int start, end, people, traversalTime;
        scanf("%d %d %d %d", &start, &end, &people, &traversalTime);

        --start;
        --end;

        for (int j = 0; j < timeSteps - traversalTime; ++j){
            dinicSolver.addEdge(start*timeSteps + j, end*timeSteps + j + traversalTime, people);
        }
    }

    int source = numVertices - 2;
    int sink = source + 1;

    // Connect the source node to the time = 0 node yay
    dinicSolver.addEdge(source, startingNode*timeSteps, groupSize);

    // Connect all safehouses to the sink node
    for (int safehouse : safehouses){
        for (int i = 0; i < timeSteps; ++i){
            dinicSolver.addEdge(safehouse*timeSteps + i, sink, INF);
        }
    }

    // Connect all subnodes of a node to each other
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < timeSteps-1; ++j){
            dinicSolver.addEdge(i*timeSteps + j, i*timeSteps + j+1, INF);
        }
    }

    // Solve and print that shit
    printf("%d\n", dinicSolver.getMaxFlow(source, sink));
}

int main(){
    // Scan in input
    int testcases;
    scanf("%d", &testcases);

    while (testcases--){
        run();
    }
}
