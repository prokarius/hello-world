import java.io.*;
import java.util.*;

public class Bicikli{
    ArrayList<HashMap<Integer, Long>> adjlist = new ArrayList<>();
    LinkedList<Integer> toposort = new LinkedList<>();
    LinkedList<Integer> cyclicNodes = new LinkedList<>();
    boolean[] visited;
    long[] ways;
    boolean flag = false;

    // Does Toposort using DFS
    private void dfs(int node){
        visited[node] = true;

        for (int i : adjlist.get(node).keySet()){
            if (!visited[i]){
                dfs(i);
            }
        }
        toposort.addFirst(node);
    }

    public void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]) + 1;
        int m = Integer.parseInt(dlist[1]);

        // Initialise the data structures
        for (int i = 0; i < n; ++i){
            adjlist.add(new HashMap<>());
        }
        visited = new boolean[n+1];
        ways = new long[n+1];

        // Populate the adjlist hashmap
        for (int i = 0; i < m; ++i){
            String[] ph = r.readLine().split(" ");
            int start = Integer.parseInt(ph[0]);
            int end = Integer.parseInt(ph[1]);
            if (adjlist.get(start).containsKey(end)){
                adjlist.get(start).put(end, adjlist.get(start).get(end) + 1);
            }
            else {
                adjlist.get(start).put(end, 1L);
            }
        }

        // First, we need to do toposort.
        dfs(1);

        // Reset the visited array
        visited = new boolean[n+1];

        // Then we process the nodes from the start.
        // We know there is 1 way to reach the first node, so we start there
        ways[1] = 1;
        for (int i : toposort){
            visited[i] = true;

            // For each outgoing edge, we just add the product of the number of ways to
            // get to the current node and the number of outgoing edges to the next node.
            for (int node : adjlist.get(i).keySet()){

                // However, if we have seen a node before, we have a loop!
                // Don't simply conclude it is a cycle though, it could be a cycle
                // that is linked to the main path, but does not directly affect it!
                if (visited[node]){

                    // Hence, we push it into this other LinkedList. We'll process
                    // these nodes later.
                    cyclicNodes.add(node);
                    continue;
                }

                // In this case, ways keeps track of the number of ways to get to a node.
                ways[node] = (ways[node] + adjlist.get(i).get(node) * ways[i]);
                if (ways[node] >= 1000000000) flag = true;
                ways[node] = ways[node] % 1000000000;
            }
        }

        // OK RIGHT! So now we need to figure out whether the nodes that are cyclic
        // can lead to the end node. Hence we gotta do DFS from them. Yay!
        // Reset the visited array
        visited = new boolean[n+1];
        for (int i : cyclicNodes){
            dfs(i);
        }

        // Then if we have visited node 2, we know the cycle affects node 2, so
        // print infinity
        if (visited[2]){
            System.out.println("inf");
            return;
        }

        // Else print that shit
        if (flag) System.out.printf("%09d\n", ways[2]);
        else System.out.println(ways[2]);
    }

    public static void main(String[] args) throws IOException{
        Bicikli bicikli = new Bicikli();
        bicikli.run();
    }
}

