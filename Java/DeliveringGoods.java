import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    int end;
    long weight;

    public Edge(int end, long weight){
        this.end = end;
        this.weight = weight;
    }

    public int compareTo(Edge other){
        return (this.weight < other.weight)?-1:1;
    }
}

public class DeliveringGoods{

    int n, m, c;

    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();
    int[] clients;
    long[] distances;

    ArrayList<ArrayList<Integer>> mcbm = new ArrayList<>();

    private long[] doDijkstra(int start){
        long[] distance = new long[n];
        for (int i = 0; i < n; ++i){
            distance[i] = 1L<<53;
        }

        PriorityQueue<Edge> dijkstra = new PriorityQueue<>();
        dijkstra.add(new Edge(start, 0));

        while (!dijkstra.isEmpty()){
            Edge edge = dijkstra.poll();
            int curr = edge.end;
            long weight = edge.weight;
            if (distance[curr] < weight) continue;
            distance[curr] = weight;

            // Visit neighbors
            for (Edge neighbor : adjlist.get(curr)){
                int end = neighbor.end;
                long newWeight = weight + neighbor.weight;
                if (distance[end] <= newWeight) continue;
                distance[end] = newWeight;
                dijkstra.add(new Edge(end, newWeight));
            }
        }

        return distance;
    }

    boolean[] visited;
    int[] forward;
    int[] backward;

    private boolean dfs(int node){
        if (visited[node]) return false;
        visited[node] = true;

        for (int neighbor : mcbm.get(node)){
            if (backward[neighbor] == -1){
                backward[neighbor] = node;
                forward[node] = neighbor;
                return true;
            }

            if (!dfs(backward[neighbor])) continue;

            backward[neighbor] = node;
            forward[node] = neighbor;
            return true;
        }

        return false;
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        String[] dlist = r.readLine().split(" ");
        n = Integer.parseInt(dlist[0]);
        m = Integer.parseInt(dlist[1]);
        c = Integer.parseInt(dlist[2]);

        clients = new int[c];
        distances = new long[c];

        // Initialise adjlist
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Find out where the clients live
        dlist = r.readLine().split(" "); 
        for (int i = 0; i < c; ++i){
            clients[i] = Integer.parseInt(dlist[i]);
            mcbm.add(new ArrayList<>());
        }

        // Get the adjlist
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            int weight = Integer.parseInt(dlist[2]);

            adjlist.get(start).add(new Edge(end, weight));
        }

        // Cool it's time to #DoDijkstra
        long[] dist = doDijkstra(0);
        for (int i = 0; i < c; ++i){
            distances[i] = dist[clients[i]];
        }

        // Do dijkstra from all node to all other nodes
        for (int i = 0; i < c; ++i){
            int start = clients[i];
            dist = doDijkstra(start);

            // Draw an edge to connect A and B if we can use the same truck:
            for (int j = 0; j < c; ++j){
                if (i == j) continue;
                if (distances[j] - distances[i] != dist[clients[j]]) continue;
                mcbm.get(i).add(j);
            }
        }

        // Time to do MCBM
        forward = new int[c];
        backward = new int[c];

        for (int i = 0; i < c; ++i){
            forward[i] = -1;
            backward[i] = -1;
        }

        int out = 0;

        // Trivial assignment
        for (int i = 0; i < c; ++i){
            for (int neighbor : mcbm.get(i)){
                if (backward[neighbor] != -1) continue;
                backward[neighbor] = i;
                forward[i] = neighbor;
                ++out;
                break;
            }
        }

        // Do MCBM
        for (int i = 0; i < c; ++i){
            if (forward[i] != -1) continue;
            visited = new boolean[c];
            if (dfs(i)) out++;
        }

        // Print the number of trucks required = c - out
        System.out.println(c - out);
    }

    public static void main(String[] args) throws IOException{
        DeliveringGoods goods = new DeliveringGoods();
        goods.run();
    }
}

