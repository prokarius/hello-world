import java.io.*;
import java.util.*;

// Encapsulates a flow edge
class FlowEdge {
    int start;
    int end;
    int flow;
    int capacity;

    public FlowEdge(int start, int end, int flow, int capacity){
        this.start = start;
        this.end = end;
        this.flow = flow;
        this.capacity = capacity;
    }

    // Getters and setters
    public int getStart(){
        return this.start;
    }

    public int getEnd(){
        return this.end;
    }

    public int getEdgeFlow(){
        return this.capacity - this.flow;
    }

    public void setFlow(int newFlow){
        this.flow += newFlow;
    }

    public boolean isSaturated(){
        return !(this.capacity - this.flow > 0);
    }
}

class DinicSolver {
    final int INF = 1<<30;

    int numVertices;
    int[] vertexIndex;
    int[] distance;
    ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();
    ArrayList<FlowEdge> edgelist = new ArrayList<>();

    // Public constructor
    public DinicSolver(int numVertices){
        this.numVertices = numVertices;
        this.vertexIndex = new int[numVertices];
        this.distance = new int[numVertices];

        for (int i = 0; i < numVertices; ++i){
            adjList.add(new ArrayList<>());
        }
    }

    // Returns true if a level graph can be found.
    private boolean bfs(int source, int sink){
        Queue<Integer> bfsQueue = new LinkedList<>();

        // Reset the distances array to all INF
        for (int i = 0; i < numVertices; ++i){
            distance[i] = INF;
        }

        distance[source] = 0;
        bfsQueue.add(source);

        // Do BFS
        while (!bfsQueue.isEmpty()){
            int curr = bfsQueue.poll();

            // If we have reached the end, just return true
            if (curr == sink) return true;

            // For each neighbour
            for (int neighbouringEdge : adjList.get(curr)){
                FlowEdge edge = edgelist.get(neighbouringEdge);

                // Continue if the edge is already saturated
                if (edge.isSaturated()) continue;

                // If we have visited the neighbour before, don't bother
                int neighbour = edge.getEnd();
                if (distance[neighbour] != INF) continue;

                // Set all the distances to the neighbours to be next higher
                distance[neighbour] = distance[curr] + 1;
                bfsQueue.add(neighbour);
            }
        }

        // We have failed to find a level graph.
        // Abort and return false.
        return false;
    }

    // Returns the flow from the source to the sink given a level graph
    private int dfs(int curr, int sink, int flow){
        // If we have reached the sink, we return flow.
        // Also return flow if there is no more flow (flow == 0)
        if (curr == sink || flow == 0) return flow;

        // Do dfs from the vertex as indicated by the vertex index
        for (int i = vertexIndex[curr]; i < adjList.get(curr).size(); ++i){
            FlowEdge forwards = edgelist.get(adjList.get(curr).get(i));
            FlowEdge backwards = edgelist.get(adjList.get(curr).get(i) ^ 1);

            // We check if the edge is not saturated
            if (forwards.isSaturated()){
                vertexIndex[curr]++;
                continue;
            }

            // We check if the edge is part of the level graph
            if (distance[forwards.getStart()] + 1 != distance[forwards.getEnd()]){
                vertexIndex[curr]++;
                continue;
            }

            // Get the amount of flow that this edge can potentially get
            // But note that the amount we can push is limited by it, or whoever
            // else is pushing flow!
            int currFlow = Math.min(forwards.getEdgeFlow(), flow);
            int amountToPush = dfs(forwards.getEnd(), sink, currFlow);

            // If we found an augmenting path, we would have a non-zero amountToPush
            if (amountToPush != 0){
                // If so, push that much flow into the current edge
                // And negative that amount into the backward edge
                forwards.setFlow(amountToPush);
                backwards.setFlow(-amountToPush);

                // Also, return the amount we push
                return amountToPush;
            }

            // Because we don't act with pointers, we have to manually update
            // vertexIndex array at the end of the for loop
            vertexIndex[curr]++;
        }

        // We have ran out of paths to go from this particular vertex.
        // We therefore return 0;
        return 0;
    }

    // Overload the dfs method, because we cannot have default arguments
    private int dfs(int source, int sink){
        return dfs(source, sink, INF);
    }

    // When we add an edge, we will create a reverse edge too
    public void addEdge (int start, int end, int capacity){
        // Create the forward and backward flow edges
        FlowEdge forwards = new FlowEdge(start, end, 0, capacity);
        FlowEdge backwards = new FlowEdge(end, start, 0, 0);

        // Push the FlowEdges into the Edgelist
        edgelist.add(forwards);
        edgelist.add(backwards);

        // Now, push the index of the edges into the adjList
        adjList.get(start).add(edgelist.size()-2);
        adjList.get(end).add(edgelist.size()-1);
    }

    // This gets the max flow from the solver
    public int getMaxFlow(int source, int sink){
        int maxFlow = 0;

        // Remember that bfs returns true if we have found a level graph
        while (bfs(source, sink)){
            // Reset the vertexIndex array
            vertexIndex = new int[numVertices];

            // Get a current flow by doing dfs and break if there is no more flow
            int flow = dfs(source, sink);
            while (flow != 0){
                // Add the new flow to the current flow otherwise
                maxFlow += flow;
                flow = dfs(source, sink);
            }
        }

        return maxFlow;
    }
}

public class NeutralGround{
    final int[] dr = {0, 1, 0, -1};
    final int[] dc = {1, 0, -1, 0};
    final int INF = 1<<20;

    int row, col;
    int[][] grid;

    public int getNodeNum(int r, int c){
        return r * col + c;
    }

    public void run() throws IOException{
        // Read in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        row = Integer.parseInt(dlist[1]);
        col = Integer.parseInt(dlist[0]);

        grid = new int[row][col];

        // Note that each vertex is now split into 2:
        // An incoming vertex, and an outgoing vertex
        // Also note that we need one more node to act as the sink and one more for
        // the source.
        // Hence we need row*col*2 + 2 vertices in total
        DinicSolver dinic = new DinicSolver(row*col*2 + 2);

        // Create a supersource and super sink
        int source = row*col*2;
        int sink = row*col*2 + 1;

        for (int i = 0; i < row; ++i){
            String phlist = r.readLine();

            for (int j = 0; j < col; ++j){
                if (phlist.charAt(j) == 'A'){
                    int outgoing = getNodeNum(i, j) * 2 + 1;
                    dinic.addEdge(source, outgoing, INF);
                }
                else if (phlist.charAt(j) == 'B'){
                    int incoming = getNodeNum(i, j) * 2;
                    dinic.addEdge(incoming, sink, INF);
                }
                else grid[i][j] = Character.getNumericValue(phlist.charAt(j));
            }
        }

        // Now we add in our edges
        // The input vertex shall be the even one
        // The output vertex shall be the odd index vertex
        for (int i = 0; i < row; ++i){
            for (int j = 0; j < col; ++j){
                if (grid[i][j] == 0) continue;
                int incoming = getNodeNum(i, j) * 2;
                dinic.addEdge(incoming, incoming + 1, grid[i][j]);
            }
        }

        // Add the all edges that connects the incoming vertex to the out going ones
        for (int i = 0; i < row; ++i){
            for (int j = 0; j < col; ++j){
                int currIncoming = getNodeNum(i, j) * 2;
                for (int k = 0; k < 4; ++k){
                    int newrow = i + dr[k];
                    int newcol = j + dc[k];

                    if (newrow < 0 || newrow >= row || newcol < 0 || newcol >= col) continue;

                    int newIncoming = getNodeNum(newrow, newcol) * 2;
                    dinic.addEdge(currIncoming + 1, newIncoming, INF);
                }
            }
        }

        // Print the output from the Dinic Solver
        System.out.println(dinic.getMaxFlow(source, sink));
    }

    public static void main(String[] args) throws IOException{
        NeutralGround solution = new NeutralGround();
        solution.run();
    }
}

