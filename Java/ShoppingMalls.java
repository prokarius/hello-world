import java.io.*;
import java.util.*;

class Location{
    int x;
    int y;
    int floor;

    public Location(int x, int y, int floor){
        this.x = x;
        this.y = y;
        this.floor = floor;
    }

    public double distTo(Location other){
        int dx = this.x - other.x;
        int dy = this.y - other.y;
        int dfloor = 5*(this.floor - other.floor);
        return Math.sqrt(dx*dx + dy*dy + dfloor*dfloor);
    }
}

public class ShoppingMalls{
    Location[] locations;

    double[][] dist;
    int[][] parent;

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Set up my data structures
        locations = new Location[n];
        parent = new int[n][n];
        dist = new double[n][n];

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                dist[i][j] = 1e200;
            }
        }

        // Read in the locations...
        for (int i = 0; i < n; ++i){
            dlist = r.readLine().split(" ");
            int floor = Integer.parseInt(dlist[0]);
            int x = Integer.parseInt(dlist[1]);
            int y = Integer.parseInt(dlist[2]);
            locations[i] = new Location(x, y, floor);
        }

        // And the connections
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            double d;

            switch(dlist[2]){
                case("lift"):
                    dist[start][end] = 1;
                    dist[end][start] = 0;
                    break;
                case("escalator"):
                    d = locations[start].distTo(locations[end]);
                    dist[start][end] = 1;
                    dist[end][start] = Math.min(dist[end][start], 3 * d);
                    break;
                case("walking"): case("stairs"):
                    d = locations[start].distTo(locations[end]);
                    dist[start][end] = Math.min(dist[start][end], d);
                    dist[end][start] = Math.min(dist[end][start], d);
            }
        }

        // Yay Floyd Warshall!
        // Set up the parent array first
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (dist[i][j] > 1e50) parent[i][j] = -1;
                else parent[i][j] = i;
            }
        }

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                for (int k = 0; k < n; ++k){
                    double newD = dist[j][i] + dist[i][k];
                    if (newD >= dist[j][k]) continue;
                    dist[j][k] = newD;
                    parent[j][k] = parent[i][k];
                }
            }
        }

        // Process queries and recover path
        int q = Integer.parseInt(r.readLine());
        for (int i = 0; i < q; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            LinkedList<Integer> out = new LinkedList<>();
            out.addFirst(end);
            while (end != start){
                end = parent[start][end];
                out.addFirst(end);
            }

            for (int loc : out){
                System.out.printf("%d ", loc);
            }
            System.out.println("");
        }
    }

    public static void main(String[] args) throws IOException{
        ShoppingMalls malls = new ShoppingMalls();
        malls.run();
    }
}

