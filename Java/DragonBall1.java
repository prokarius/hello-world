import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    int end;
    long cost;

    public Edge(int end, long cost){
        this.end = end;
        this.cost = cost;
    }

    public int compareTo(Edge other){
        return (this.cost > other.cost)?1:-1;
    }
}

public class DragonBall1{

    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();
    int[] balls = new int[8];
    long[][] shortestPath = new long[8][8];

    long best = 1L<<55;

    PriorityQueue<Edge> dijkstra;
    long[] distance;
    boolean[] visited;

    private void doDijkstra(int start){
        dijkstra = new PriorityQueue<>();
        dijkstra.add(new Edge(start, 0));

        distance[start] = 0;
        visited[start] = true;

        while (!dijkstra.isEmpty()){
            Edge curr = dijkstra.poll();
            int end = curr.end;
            long cost = curr.cost;

            // Have we been here before or for cheaper?
            if (visited[end] & distance[end] < cost) continue;

            // Visit all neighbors
            for (Edge e : adjlist.get(end)){
                int neighbor = e.end;
                long nextCost = e.cost;
                long newCost = cost + nextCost;

                if (distance[neighbor] <= newCost) continue;
                distance[neighbor] = newCost;
                visited[neighbor] = true;

                dijkstra.add(new Edge(neighbor, newCost));
            }
        }
    }

    private void tsp(int curr, int bitmask, long cost){
        // Have we reached the end?
        if (bitmask == 255){
            best = Math.min(best, cost);
            return;
        }

        // Do a recursive thingie
        for (int i = 1; i < 8; ++i){
            int mask = 1<<i;
            if ((bitmask & mask) > 0) continue;

            int newBitmask = bitmask + mask;
            long newCost = cost + shortestPath[curr][i];

            tsp(i, newBitmask, newCost);
        }
    }

    private void run() throws IOException{ 
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }
        
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]) - 1;
            int end = Integer.parseInt(dlist[1]) - 1;
            int cost = Integer.parseInt(dlist[2]);

            adjlist.get(start).add(new Edge(end, cost));
            adjlist.get(end).add(new Edge(start, cost));
        }

        dlist = r.readLine().split(" "); 
        for (int i = 0; i < 7; ++i){
            balls[i+1] = Integer.parseInt(dlist[i]) - 1;
        }

        // We want to get the distances from all balls to all balls
        for (int i = 0; i < 8; ++i){
            // Reset distance array
            distance = new long[n];
            visited = new boolean[n];

            for (int j = 0; j < n; ++j){
                distance[j] = 1L << 50;
            }

            doDijkstra(balls[i]);

            // Now distance array has the distances from a to b
            for (int j = 0; j < 8; ++j){
                shortestPath[i][j] = distance[balls[j]];
            }
        }

        // Cool, now do TSP.
        tsp(0, 1, 0);

        // Print the best!
        if (best >= 1L << 50){
            System.out.println("-1");
        }
        else {
            System.out.println(best);
        }
    }

    public static void main(String[] args) throws IOException{
        DragonBall1 dragonBall = new DragonBall1();
        dragonBall.run();
    }
}

