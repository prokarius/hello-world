import java.util.*;
import java.io.*;

public class Internet{
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    boolean[] visited;

    private void dfs(int node){
        if (visited[node]){
            return;
        }
        visited[node] = true;
        for (int neighbour : adjlist.get(node)){
            dfs(neighbour);
        }
    }

    public void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String[] phlist = r.readLine().split(" ");
        int n = Integer.parseInt(phlist[0]);
        int m = Integer.parseInt(phlist[1]);

        // Initialise adjlist
        for (int i = 0; i <= n; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Initialise visited array
        visited = new boolean[n+1];

        // Scan in the edges
        for (int i = 0; i < m; ++i){
            String[] dlist = r.readLine().split(" ");
            int nodeA = Integer.parseInt(dlist[0]);
            int nodeB = Integer.parseInt(dlist[1]);
            adjlist.get(nodeA).add(nodeB);
            adjlist.get(nodeB).add(nodeA);
        }

        // Do a DFS to see which nodes can be visited from 1
        dfs(1);

        boolean flag = true;
        OutputStream log = new BufferedOutputStream (System.out);
        for (int i = 1; i <= n; ++i){
            if (!visited[i]){
                log.write(String.valueOf(i).getBytes());
                log.write('\n');
                flag = false;
            }
        }

        log.flush();

        if (flag){
            System.out.println("Connected");
        }
    }

    public static void main(String[] args) throws IOException{
        Internet solution = new Internet();
        solution.run();
    }
}
