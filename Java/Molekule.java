import java.util.*;
import java.io.*;

public class Molekule{
    int[] edges;
    int[] colors;

    ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();

    private void dfs(int node, int color){
        // Set the node color to the color:
        colors[node] = color;

        // Visit all the neighbors
        for (int neighbor : adjList.get(node)){
            if (colors[neighbor] != 0) continue;
            dfs(neighbor, 3 - color);
        }
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());

        // Initialize my data structures
        edges = new int[n];
        colors = new int[n];

        for (int i = 0; i < n; ++i){
            adjList.add(new ArrayList<>());
        }

        for (int i = 0; i < n-1; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]) - 1;
            int end = Integer.parseInt(dlist[1]) - 1;

            edges[i] = start;

            adjList.get(start).add(end);
            adjList.get(end).add(start);
        }

        // Do DFS
        dfs(0, 1);

        // Print the colors
        for (int i = 0; i < n-1; ++i){
            System.out.println(colors[edges[i]] == 1?"0":"1");
        }
    }

    public static void main(String[] args) throws IOException{
        Molekule molekule = new Molekule();
        molekule.run();
    }
}

