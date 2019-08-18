#include<stdio.h>
#include<stdlib.h>

#define MAXNODES 300005

typedef struct {
    int start;
    int end;
} Edge;

Edge edge(int start, int end){
    Edge out;

    // Ensure that start < end always
    if (start > end){
        int temp = start;
        start = end;
        end = temp;
    }

    out.start = start;
    out.end = end;
    return out;
}

int cmpfunc(const void* a, const void* b){
    Edge first = *(Edge*) a;
    Edge second = *(Edge*) b;
    if (first.start == second.start){
        return first.end - second.end;
    }
    return first.start - second.start;
}

int equal(Edge a, Edge b){
    return (a.start == b.start && a.end == b.end);
}

// Stores the mapping between input number and actual node number
int mapping[MAXNODES];
int numNodes = 0;

int getMapping(int node){
    if (mapping[node] != -1){
        return mapping[node];
    }
    mapping[node] = numNodes;
    ++numNodes;
    return numNodes - 1;
}

// Edgelist with and without duplicates
Edge edgeList[MAXNODES];
Edge actualEdgeList[MAXNODES];
int numEdges = 0;

// stores the size of the adjacency list for quick lookup
int adjListSize[MAXNODES];
int* adjList[MAXNODES];

// For our queries
int querySize[MAXNODES];
int* toQuery[MAXNODES];

// Visited array
int visited[MAXNODES];

// Gets the edge with the larger degree. Optimisation
int getBigger(Edge e){
    if (adjListSize[e.start] > adjListSize[e.end]) return e.start;
    if (adjListSize[e.start] < adjListSize[e.end]) return e.end;
    return (e.start > e.end)?(e.start):(e.end);
}

// Push the edge into the edgelist
void pushEdgeList(Edge e){
    actualEdgeList[numEdges] = e;
    numEdges++;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);
    --n;

    // Short circuit if there are no edges
    if (n == 0){
        printf("0\n");
        return 0;
    }

    // Reset the mapping
    for (int i = 0; i <= n+1; ++i){
        mapping[i] = -1;
    }

    for (int i = 0; i < n; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        int mappedStart = getMapping(start);
        int mappedEnd = getMapping(end);
        edgeList[i] = edge(mappedStart, mappedEnd);
    }

    // Well one easy way to get rid of duplicates is to sort
    qsort(edgeList, n, sizeof(Edge), cmpfunc);

    // Process the edges left to right
    Edge curr = edge(-1000007, -1000007);

    for (int i = 0; i < n; ++i){
        Edge next = edgeList[i];
        if (equal(curr, next)) continue;
        adjListSize[next.start]++;
        adjListSize[next.end]++;
        pushEdgeList(next);
        curr = next;
    }

    // Create the adjList now, using MALLOC!!!
    for (int i = 0; i < numNodes; ++i){
        adjList[i] = (int*) malloc(adjListSize[i] * sizeof(int));
    }

    // Go into each of the lists and fill!
    // MY NAME IS DOBBY.
    int* populate = (int*) calloc(numNodes, sizeof(int));
    for (int i = 0; i < numEdges; ++i){
        int start = actualEdgeList[i].start;
        int end = actualEdgeList[i].end;
        adjList[start][populate[start]] = end;
        adjList[end][populate[end]] = start;
        populate[start]++;
        populate[end]++;
    }

    // DOBBY HAS NO MASTER, DOBBY IS A FREE ELF!
    free(populate);

    // Right, now we calculate all paths of length 2
    long long out = 0;
    for (int i = 0; i < numNodes; ++i){
        out += (adjListSize[i] * (long long) (adjListSize[i] - 1)) / 2;
    }

    // We get a list of edges to query:
    for (int i = 0; i < numEdges; ++i){
        int bigger = getBigger(actualEdgeList[i]);
        int smaller;
        if (bigger == actualEdgeList[i].start){
            smaller = actualEdgeList[i].end;
        }
        else {
            smaller = actualEdgeList[i].start;
        }
        ++querySize[bigger];
    }

    // Create the population list.
    for (int i = 0; i < numNodes; ++i){
        if (querySize[i] != 0){
            toQuery[i] = malloc(querySize[i] * sizeof(int));
        }
    }

    // The populate the population list
    // DOBBY IS BACK
    populate = (int*) calloc(numNodes, sizeof(int));
    for (int i = 0; i < numEdges; ++i){
        int bigger = getBigger(actualEdgeList[i]);
        int smaller;
        if (bigger == actualEdgeList[i].start){
            smaller = actualEdgeList[i].end;
        }
        else {
            smaller = actualEdgeList[i].start;
        }
        toQuery[bigger][populate[bigger]] = smaller;
        ++populate[bigger];
    }

    // DOBBY HAS NO MASTER, DOBBY IS A FREE ELF
    free(populate);

    // For each of my nodes, skip it if we have no queries
    for (int i = 0; i < numNodes; ++i){
        if (querySize[i] == 0) continue;

        // Mark all the neighbours as visited
        for (int j = 0; j < adjListSize[i]; ++j){
            visited[adjList[i][j]] = 1;
        }

        // For each of the queries, find their neighbours and see if we can visit
        // any of the marked cells. If so, minus
        for (int j = 0; j < querySize[i]; ++j){
            int neighbour = toQuery[i][j];

            for (int k = 0; k < adjListSize[neighbour]; ++k){
                if (visited[adjList[neighbour][k]]) out--;
            }
        }

        // Unmark all the neighbours as visited
        for (int j = 0; j < adjListSize[i]; ++j){
            visited[adjList[i][j]] = 0;
        }
    }

    // Finally we are done, print that shit out
    printf("%lld\n", out * 2);

    return 0;
}


/* JAVA SOLUTION THAT TLE. TWICE
   WHY JAVA SO SLOW WTF

 import java.io.*;
import java.util.*;

public class GottaCatchEmAll{
    class Edge{
        int start;
        int end;

        public Edge(int start, int end){
            this.start = start;
            this.end = end;
        }

        public int getBigger(){
            int startsize = adjList.get(this.start).size();
            int endsize = adjList.get(this.end).size();
            if (startsize > endsize){
                return this.start;
            }
            if (endsize > startsize){
                return this.end;
            }
            return Math.max(this.start, this.end);
        }
    }

    ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();

    // We maybe have less vertices than edges
    HashMap<Integer, Integer> vertices = new HashMap<>();
    int numNodes = 0;

    private int getMapping(int node){
        if (vertices.containsKey(node)){
            return vertices.get(node);
        }
        vertices.put(node, numNodes);
        ++numNodes;
        return numNodes - 1;
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        int n = Integer.parseInt(r.readLine());
        --n;

        // Initialise the edge and adj lists
        Edge[] originalEdges = new Edge[n];
        ArrayList<Edge> edgelist = new ArrayList<>(n);

        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = getMapping(Integer.parseInt(dlist[0]));
            int end = getMapping(Integer.parseInt(dlist[1]));
            originalEdges[i] = new Edge(start, end);
        }

        // Create the adjlist
        for (int i = 0; i < numNodes; ++i){
            adjList.add(new ArrayList<>());
        }

        for (Edge e: originalEdges){
            int start = e.start;
            int end = e.end;

            // Do not add the edge if it already has been seen before
            if (!adjList.get(start).contains(end)){
                adjList.get(start).add(end);
                adjList.get(end).add(start);
                edgelist.add(e);
            }
        }

        // Initially, the number of paths is a tree, which is (deg * deg-1).
        // But we don't count symmetries for now.
        // By keeping the symmetries computation to the final step, we save quite
        // half the number of operations.
        long out = 0;
        for (int i = 0; i < numNodes; ++i){
            int size = adjList.get(i).size();
            out += size * (long) (size - 1) / 2;
        }

        // Now process the list of edges. We want to optimise the edges that we
        // process. Essentially, we make it so that we only need to process the
        // smallest number of nodes. This is the hack
        HashMap<Integer, ArrayList<Integer>> toQuery = new HashMap<>();

        // Since we are not counting symmetries, we can essentially process half of
        // each edge. Hence instead of pushing both sides into the list of queries,
        // we just find the edge that is larger, and push it in.
        for (Edge e: edgelist){
            int larger = e.getBigger();
            int smaller;
            if (larger == e.start){
                smaller = e.end;
            }
            else {
                smaller = e.start;
            }
            if (!toQuery.containsKey(larger)){
                toQuery.put(larger, new ArrayList<>());
            }
            toQuery.get(larger).add(smaller);
        }

        // OK now process for each point that we will be querying
        boolean[] visited = new boolean[numNodes];
        for (int i = 0; i < numNodes; ++i){
            if (!toQuery.containsKey(i)) continue;

            // Mark the neighbours of the current point as visited
            for (int queryPoint : adjList.get(i)){
                visited[queryPoint] = true;
            }

            // Now for each of the other points that is connected to this node, we
            // check if their neighbours can reach the neighbours of our current point
            for (int neighbour : toQuery.get(i)){
                for (int neighbourOfNeighbour : adjList.get(neighbour)){

                    // If we have visited here before, this means there is a direct
                    // path from our current node to this particular node.
                    // Therefore get rid of one of the paths to here
                    if (visited[neighbourOfNeighbour]) out--;
                }
            }

            // Unmark the neighbours of the current point as visited
            for (int queryPoint : adjList.get(i)){
                visited[queryPoint] = false;
            }
        }

        // Account for the symmetries by multiplying by 2
        System.out.println(out * 2);
    }

    public static void main(String[] args) throws IOException{
        GottaCatchEmAll Pokenom = new GottaCatchEmAll();
        Pokenom.run();
    }
}

*/
