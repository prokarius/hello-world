import java.util.*;
import java.io.*;

public class IsaHasa{
    private static final int MAX_NODES = 500;

    private HashMap<String, Integer> mapping;
    private ArrayList<ArrayList<Integer>> adjlist;

    private boolean[][] adjmatrix = new boolean[MAX_NODES][2*MAX_NODES];

    public IsaHasa() {
        mapping = new HashMap<>();
        adjlist = new ArrayList<>();
    }

    // Returns if nodea is connected to nodeb
    private boolean isConnected(int nodea, int nodeb){
        return adjmatrix[nodea][nodeb];
    }

    // Returns the Hash value of a given string
    private int getHash(String s){
        if (mapping.containsKey(s)){
            return mapping.get(s);
        }
        else {
            int newHash = mapping.size();
            mapping.put(s, newHash);
            return newHash;
        }
    }

    public void dfs(int nodefrom, int nodeto){
        adjmatrix[nodefrom][nodeto] = true;
        for (int i : adjlist.get(nodeto)){
            if (!adjmatrix[nodefrom][i]){
                dfs(nodefrom, i);
            }
        }
    }

    // Run method. Main solution
    public void run() throws IOException{
        // Fill up the adjlist with ArrayLists
        for (int i = 0; i < 2 * MAX_NODES; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] phlist = r.readLine().split(" ");
        int n = Integer.parseInt(phlist[0]);
        int q = Integer.parseInt(phlist[1]);

        // For each relationship
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int hasha = getHash(dlist[0]);
            int hashb = getHash(dlist[2]);

            // If it's a is-a relationship
            // We connect the red nodes with red nodes
            // and blue nodes with blue nodes
            if (dlist[1].equals("is-a")){
                adjlist.get(hasha).add(hashb);
                adjlist.get(hasha + MAX_NODES).add(hashb + MAX_NODES);
            }
            // Else, we connect the red nodes with the
            // blue nodes in one direction
            else { // has-a relationship
                adjlist.get(hasha).add(hashb + MAX_NODES);
                adjlist.get(hasha + MAX_NODES).add(hashb + MAX_NODES);
            }
        }

        // Generate the adjmatrix. This will speed up processing
        for (int i = 0; i < mapping.size(); ++i){
            dfs(i, i);
        }

        // Lastly, for each query, we check if we can reach
        // the corresponding nodes.
        for (int i = 1; i <= q; ++i){
            System.out.printf("Query %d: ", i);
            String[] dlist = r.readLine().split(" ");
            int hasha = getHash(dlist[0]);
            int hashb = getHash(dlist[2]);

            // is-a = red to red
            if (dlist[1].equals("is-a")){
                System.out.println(isConnected(hasha, hashb));
            }
            // has-a = red to blue
            else {
                System.out.println(isConnected(hasha, hashb + MAX_NODES));
            }
        }
    }

    public static void main(String[] args) throws IOException{
        IsaHasa solution = new IsaHasa();
        solution.run();
    }
}
