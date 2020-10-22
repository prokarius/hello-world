import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    int end;
    int fuel;
    int cost;

    public Edge(int end, int fuel){
        this.end = end;
        this.fuel = fuel;
        this.cost = 0;
    }

    public Edge(int end, int fuelLeft, int cost){
        this.end = end;
        this.fuel = fuelLeft;
        this.cost = cost;
    }

    public int compareTo(Edge other){
        return (this.cost - other.cost);
    }
}

public class FullTank{
    int[] cost;

    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();

    private void doDijkstra(int start, int end, int capacity, int n){
        // Initialise dp array
        int[][] visited = new int[n][capacity+1];
        for (int i = 0; i < n; ++i){
            for (int j = 0; j <= capacity; ++j){
                visited[i][j] = 1<<30;
            }
        }

        PriorityQueue<Edge> dijkstra = new PriorityQueue<>();

        // Add the start city's edges into the HeapQueue
        for (int i = 0; i <= capacity; ++i){
            dijkstra.add(new Edge(start, i, i*cost[start]));
            visited[start][i] = i*cost[start];
        }


        // While we have not reached the end
        int out = 1<<30;
        while (!dijkstra.isEmpty()){
            Edge edge = dijkstra.poll();
            int curr = edge.end;
            int fuel = edge.fuel;
            int currCost = edge.cost;

            // Have we been here before?
            if (visited[curr][fuel] < currCost) continue;

            // Have we reached the end?
            if (curr == end){
                out = currCost;
                dijkstra.clear();
                continue;
            }

            // Go to the neighbors:
            for (Edge next : adjlist.get(curr)){
                int neighbor = next.end;
                int dist = next.fuel;

                // Can we make it there?
                if (dist > fuel) continue;

                // Traverse only if we have not been there yet.
                int fuelLeft = fuel-dist;
                for (int i = 0; i + fuelLeft <= capacity; ++i){
                    int nextCost = currCost + i*cost[neighbor];

                    if (visited[neighbor][i + fuelLeft] < nextCost) continue;

                    visited[neighbor][i + fuelLeft] = nextCost;
                    dijkstra.add(new Edge(neighbor, i + fuelLeft, nextCost));
                }
            }
        }

        // Have we reached the end?
        if (out < 1<<30){
            System.out.println(out);
        }
        else {
            System.out.println("impossible");
        }
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        cost = new int[n];

        dlist = r.readLine().split(" "); 
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
            cost[i] = Integer.parseInt(dlist[i]);
        }

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            int cost = Integer.parseInt(dlist[2]);

            adjlist.get(start).add(new Edge(end, cost));
            adjlist.get(end).add(new Edge(start, cost));
        }

        int q = Integer.parseInt(r.readLine());
        for (int i = 0; i < q; ++i){
            dlist = r.readLine().split(" ");
            int capacity = Integer.parseInt(dlist[0]);
            int start = Integer.parseInt(dlist[1]);
            int end = Integer.parseInt(dlist[2]);

            doDijkstra(start, end, capacity, n);
        }
    }

    public static void main(String[] args) throws IOException{
        FullTank tank = new FullTank();
        tank.run();
    }
}

