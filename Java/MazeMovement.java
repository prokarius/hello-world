import java.io.*;
import java.util.*;

class EdmondKarp{
    private int n;
    private int[][] cap;
    private int[][] flow;
    private ArrayList<ArrayList<Integer>> adjList;

    public EdmondKarp(int n){
        this.n = n;
        cap = new int[n][n];
        flow = new int[n][n];
        adjList = new ArrayList<>();
        for (int i = 0; i < n; ++i){
            adjList.add(new ArrayList<>());
        }
    }

    public void addEdge(int start, int end, int capacity){
        cap[start][end] = capacity;
        cap[end][start] = capacity;

        adjList.get(start).add(end);
        adjList.get(end).add(start);
    }

    // This is the BFS
    private ArrayList<Integer> getAugmentingPath(int source, int sink){
        int[] comesFrom = new int[n];
        boolean[] visited = new boolean[n];
        Queue<Integer> queue = new LinkedList<>();
        queue.add(source);
        comesFrom[source] = -1;
        visited[source] = true;

        // Do BFS
        while (!queue.isEmpty()){
            int curr = queue.poll();

            if (curr == sink) break;

            for (int neighbour : adjList.get(curr)){
                if (visited[neighbour]) continue;
                if (cap[curr][neighbour] - flow[curr][neighbour] == 0) continue;
                comesFrom[neighbour] = curr;
                visited[neighbour] = true;
                queue.add(neighbour);
            }
        }

        // If we did not reach the end, then return null
        if (!visited[sink]) return null;

        // If now, we get the path
        ArrayList<Integer> path = new ArrayList<>();
        int curr = sink;

        while (curr != -1){
            path.add(curr);
            curr = comesFrom[curr];
        }

        Collections.reverse(path);
        return path;
    }

    // Returns an integer representing amount of flow that was newly created
    // Augments the path during this method
    private int augmentPath(ArrayList<Integer> path){
        int amountToPush = 1<<30;
        for (int node = 0; node < path.size()-1; ++node){
            int from = path.get(node);
            int to = path.get(node + 1);
            amountToPush = Math.min(amountToPush, cap[from][to] - flow[from][to]);
        }

        // Actually change the flow of the graph
        for (int node = 0; node < path.size()-1; ++node){
            int from = path.get(node);
            int to = path.get(node + 1);
            flow[from][to] += amountToPush;
            flow[to][from] -= amountToPush;
        }

        return amountToPush;
    }

    // Main solve method, performs Edmond Karp's algorithm
    public int getMaxFlow(int source, int sink){
        int maxFlow = 0;

        while (true){
            ArrayList<Integer> path = getAugmentingPath(source, sink);
            if (path == null) break;

            maxFlow += augmentPath(path);
        }

        return maxFlow;
    }
}

public class MazeMovement{
    int[] values;
    EdmondKarp edmondKarp;

    // This is in defiance of 2103T >:(
    private int getGCD(int a, int b){
       if (b == 0) return a;
       return getGCD(b, a%b);
    }

    public void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        values = new int[n];
        edmondKarp = new EdmondKarp(n);

        int source = 0;
        int sink = 0;

        for (int i = 0; i < n; ++i){
            values[i] = Integer.parseInt(r.readLine());
            if (values[source] > values[i]) source = i;
            if (values[sink] < values[i]) sink = i;
        }

        // Populate the edges.
        for (int i = 0; i < n-1; ++i){
            for (int j = i+1; j < n; ++j){
                int gcd = getGCD(values[i], values[j]);
                if (gcd == 1) continue;
                edmondKarp.addEdge(i, j, gcd);
            }
        }

        // Print that shit
        System.out.println(edmondKarp.getMaxFlow(source, sink));
    }

    public static void main(String[] args) throws IOException{
        MazeMovement maze = new MazeMovement();
        maze.run();
    }
}
