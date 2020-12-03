import java.io.*;
import java.util.*;

public class MoneyMatters{
    
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    int[] owe;
    boolean[] visited;
    int total;

    // For each connected component, see if the amount owed sums to 0
    private void processClique(int node){
        visited[node] = true;
        total += owe[node];
        for (int neighbor : adjlist.get(node)){
            if (visited[neighbor]) continue;
            processClique(neighbor);
        }
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Initialize data structures
        owe = new int[n];
        visited = new boolean[n];
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
            owe[i] = Integer.parseInt(r.readLine());
        }

        // Friendships
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            adjlist.get(start).add(end);
            adjlist.get(end).add(start);
        }

        // Do DFS
        boolean out = true;
        for (int i = 0; i < n; ++i){
            if (visited[i]) continue;
            total = 0;
            processClique(i);
            out &= (total == 0);
        }

        System.out.printf(out ? "" : "IM");
        System.out.println("POSSIBLE");
    }

    public static void main(String[] args) throws IOException{
        MoneyMatters money = new MoneyMatters();
        money.run();
    }
}

