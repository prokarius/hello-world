import java.io.*;
import java.util.*;

public class Collapse{
    LinkedList<Integer> queue = new LinkedList<>();
    ArrayList<HashMap<Integer, Integer>> adjList = new ArrayList<>();
    int[] required;
    int[] current;
    boolean[] ded;

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());

        // Set up the adjList and data structures
        for (int i = 0; i <= n; ++i){
            adjList.add(new HashMap<>());
        }
        required = new int[n+1];
        current = new int[n+1];
        ded = new boolean[n+1];

        for (int i = 1; i <= n; ++i){
            String[] dlist = r.readLine().split(" ");
            int goodsRequired = Integer.parseInt(dlist[0]);
            int numIslands = Integer.parseInt(dlist[1]);

            required[i] = goodsRequired;

            // Parse the island data:
            for (int j = 2; j < 2 * (1 + numIslands); j+=2){
                int receivingIsland = Integer.parseInt(dlist[j]);
                int receivingAmount = Integer.parseInt(dlist[j+1]);

                // Say that the receiving island is sending x amount of goods to the
                // current island
                current[i] += receivingAmount;
                adjList.get(receivingIsland).put(i, receivingAmount);
            }
        }

        // Now collapse the first island
        queue.addLast(1);
        ded[1] = true;

        // Check for any other islands that are going to collapse too:
        for (int i = 2; i <= n; ++i){
            if (current[i] < required[i]){
                queue.addLast(i);
                ded[i] = true;
            }
        }

        while (!queue.isEmpty()){
            int curr = queue.pollFirst();
            n--;
            HashMap<Integer, Integer> connections = adjList.get(curr);

            // For each of the islands the current island contributes to, stop
            // sending goods
            for (int island : connections.keySet()){
                int amount = connections.get(island);
                current[island] -= amount;

                // If the island cannot survive, then add it to the ded list
                if (!ded[island] && current[island] < required[island]){
                    queue.addLast(island);
                    ded[island] = true;
                }
            }
        }

        // Print out the number of islands left
        System.out.println(n);
    }

    public static void main(String[] args) throws IOException{
        Collapse collapse = new Collapse();
        collapse.run();
    }
}
