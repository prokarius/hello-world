import java.io.*;
import java.util.*;

class Edge{
    int end;
    int dist;

    public Edge (int end, int dist){
        this.end = end;
        this.dist = dist;
    }
}

public class ChickenJoggers{
    int n, s;
    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();
    boolean[] lamp;
    boolean[] visited;

    private void dfs(int curr, int distance){
        // Are we too far from the uni?
        if (distance * 2 >= s) return;

        for (Edge edge : adjlist.get(curr)){
            int neighbor = edge.end;
            int dist = edge.dist;

            // Have we been here before?
            if (visited[neighbor]) continue;
            visited[neighbor] = true;

            dfs(neighbor, distance + dist);
        }
    }

    int[][] memo;

    private int mvc(int curr, int prev, boolean prevChoice){
        // Have we been here before?
        int second = prevChoice?1:0;
        if (memo[curr][second] != -1) return memo[curr][second];

        // Choose to put a lamp here
        int numLampsYes = 1;
        for (Edge edge : adjlist.get(curr)){
            int neighbor = edge.end;
            if (neighbor == prev) continue;
            if (!visited[neighbor]) continue;
            numLampsYes += mvc(neighbor, curr, true);
        }

        // If there is already a lamp here, subtract 1
        if (lamp[curr]) numLampsYes--;

        // Choose not to put a lamp here
        // We can only do it if our parent has a lamp
        int numLampsNo = 1<<30;
        if (prevChoice){ 
            numLampsNo = 0;
            for (Edge edge : adjlist.get(curr)){
                int neighbor = edge.end;
                if (neighbor == prev) continue;
                if (!visited[neighbor]) continue;

                numLampsNo += mvc(neighbor, curr, false);
            }
        }

        // Memoize!
        memo[curr][second] = Math.min(numLampsYes, numLampsNo);
        return memo[curr][second];
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        String[] dlist = r.readLine().split(" ");
        n = Integer.parseInt(dlist[0]);
        s = Integer.parseInt(dlist[1]);

        lamp = new boolean[n];
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        for (int i = 0; i < n-1; ++i){
            dlist = r.readLine().split(" ");
            int a = Integer.parseInt(dlist[0]) - 1; // WHY ARE ALL THE INPUTS
            int b = Integer.parseInt(dlist[1]) - 1; // ONE INDEXED?!
            int d = Integer.parseInt(dlist[2]);

            adjlist.get(a).add(new Edge(b, d));
            adjlist.get(b).add(new Edge(a, d));
        }

        int l = Integer.parseInt(r.readLine());
        dlist = r.readLine().split(" ");
        
        for (int i = 0; i < l; ++i){
            lamp[Integer.parseInt(dlist[i]) - 1] = true;
        }

        // Now we do DFS to see which intersections we need to consider
        visited = new boolean[n];
        visited[0] = true;
        dfs(0, 0);

        // Set up my memo table
        memo = new int[n][2];
        for (int i = 0; i < n; ++i){
            memo[i][0] = -1;
            memo[i][1] = -1;
        }

        // Here, visited array tells me which edges are visited
        // Run MVC algo, and allow node 0 to be either on or off.
        System.out.println(mvc(0, -1, true));
    }

    public static void main(String[] args) throws IOException{
        ChickenJoggers jogger = new ChickenJoggers();
        jogger.run();
    }
}

