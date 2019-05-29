import java.io.*;
import java.util.*;

public class Grapevine{
    // Stores the name to hash
    HashMap<String, Integer> mapping = new HashMap<>();

    // Number of people that needs to be convinced before treshold tips.
    int[] threshold;

    // Adjlist of connections
    // Suddenly paranoid because I can't remember if it's expensive to initialise
    // 100k ArrayLists...
    HashMap<Integer, ArrayList<Integer>> adjlist = new HashMap<>();

    // Overall Data structures for the BFS
    LinkedList<Integer> queued = new LinkedList<>();
    boolean[] visited;
    boolean[] heard;

    private void bfs(){
        LinkedList<Integer> bfsQueue = new LinkedList<>();

        // These are all the infected people. For each of them:
        for (int curr : queued){

            // Check to see if there is an entry in the adj list for this
            if (!adjlist.containsKey(curr)) continue;

            // For each neighbour, subtract 1 from their threshold
            // Only do to if they are not visited though
            for (int neighbour : adjlist.get(curr)){
                if (visited[neighbour]) continue;

                heard[neighbour] = true;
                threshold[neighbour]--;

                // If the threshold is 0, push them into the stack
                if (threshold[neighbour] == 0){
                    visited[neighbour] = true;
                    bfsQueue.push(neighbour);
                }
            }
        }
        queued = bfsQueue;
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);
        int d = Integer.parseInt(dlist[2]);

        // Initialise all my arrays
        visited = new boolean[n];
        heard = new boolean[n];
        threshold = new int[n];

        // We can be sure all these strings are unique
        for (int i = 0; i < n; ++i){
            dlist = r.readLine().split(" ");
            int skepticism = Integer.parseInt(dlist[1]);

            // Save the mapping of the name to the index
            mapping.put(dlist[0], i);

            // Save the thresholds
            threshold[i] = skepticism;
        }

        // Make the adjmatrix
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int index1 = mapping.get(dlist[0]);
            int index2 = mapping.get(dlist[1]);

            // Try to push into the adjlist
            if (!adjlist.containsKey(index1)){
                adjlist.put(index1, new ArrayList<>());
            }
            adjlist.get(index1).add(index2);

            if (!adjlist.containsKey(index2)){
                adjlist.put(index2, new ArrayList<>());
            }
            adjlist.get(index2).add(index1);
        }

        // Get the troublesome and push into the BFS
        int starting = mapping.get(r.readLine());

        queued.push(starting);
        threshold[starting] = 1;
        heard[starting] = true;
        visited[starting] = true;

        for (int i = 0; i < d; ++i){
            bfs();
        }

        // Print the result
        int infected = -1;
        for (int i = 0; i < n; ++i){
            if (heard[i]) infected++;
        }
        System.out.println(infected);
    }

    public static void main(String[] args) throws IOException{
        Grapevine grapevine = new Grapevine();
        grapevine.run();
    }
}
