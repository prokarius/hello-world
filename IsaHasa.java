import java.util.*;
import java.io.*;

public class IsaHasa{
    private static final int MAX_NODES = 500;

    private HashMap<String, Integer> mapping;
    private ArrayList<ArrayList<Integer>> adjlist;

    public IsaHasa() {
        mapping = new HashMap<>();
        adjlist = new ArrayList<>();
    }

    // Returns the Hash value of a given string
    private int getHash(String s){
        if (this.mapping.containsKey(s)){
            return mapping.get(s);
        }
        else {
            int newHash = mapping.size();
            mapping.put(s, newHash);
            return newHash;
        }
    }

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
            // 
            if (dlist[1].equals("is-a")){
                adjlist.get(hasha).add(hashb);
                adjlist.get(hasha + MAX_NODES).add(hashb + MAX_NODES);
            }
            else { // has-a relationship
                //pass;
            }
        }
    }

    public static void main(String[] args) throws IOException{
        IsaHasa solution = new IsaHasa();
        solution.run();
    }
}
