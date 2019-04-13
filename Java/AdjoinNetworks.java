import java.io.*;
import java.util.*;

class Pair{
    int node;
    int distance;

    public Pair(int node, int distance){
        this.node = node;
        this.distance = distance;
    }

    public int getNode(){
        return this.node;
    }

    public int getDistance(){
        return this.distance;
    }
}

public class AdjoinNetworks{
    private HashMap<Integer, ArrayList<Integer>> adjlist = new HashMap<>();
    private boolean visited[][];

    // Standard BFS.
    // Returns a pair of node and distance to that node from a given starting node
    private Pair bfs(int starting, int turn){
        LinkedList<Pair> queue = new LinkedList<>();
        Pair output = new Pair(starting, 0);
        queue.add(output);

        while (!queue.isEmpty()){
            output = queue.pollLast();
            int currentNode = output.getNode();
            int currentDistance = output.getDistance();
            for (Integer neighbour : adjlist.get(currentNode)){
                if (visited[neighbour][turn]) continue;
                visited[neighbour][turn] = true;
                queue.addFirst(new Pair(neighbour, currentDistance + 1));
            }
        }
        return output;
    }

    // To get the longest path, choose a starting point,
    // Find the furthest point from this starting point and BFS from there.
    private int getLongestPath(int start){
        Pair furthest = bfs(start, 0);
        return bfs(furthest.getNode(), 1).getDistance();
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int c = Integer.parseInt(dlist[0]);
        int l = Integer.parseInt(dlist[1]);

        visited = new boolean[c][2];

        for (int i = 0; i < l; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            if (!adjlist.containsKey(start)){
                adjlist.put(start, new ArrayList<>());
            }
            if (!adjlist.containsKey(end)){
                adjlist.put(end, new ArrayList<>());
            }
            adjlist.get(start).add(end);
            adjlist.get(end).add(start);
        }

        // Create the list of trees, and add sentinel values
        ArrayList<Integer> radius = new ArrayList<>();
        radius.add(100);
        radius.add(100);
        
        // If there are less keys in the keyset, that means we have some solo nodes
        // Add them to the radius list too.
        int numSoloNodes = c - adjlist.keySet().size();
        numSoloNodes = Math.min(3, numSoloNodes);
        for (int i = 0; i < numSoloNodes; ++i){
            radius.add(1);
        }

        // Find the diameters of all the trees
        for (Integer node : adjlist.keySet()){
            if (visited[node][0]) continue;
            int diameter = getLongestPath(node);
            radius.add(-diameter);
        }

        // Sort the diameters
        Collections.sort(radius);

        // The longest path is the max of
        // 1) The diameter of the longest tree
        // 2) Radius of 1st and 2nd largest tree + 1
        // 3) Radius of 2nd and 3rd largest tree + 2 
        //    (Happens when top 3 trees are of same height)
        int best = Math.max(-radius.get(0), // Case 1
                        Math.max(
                            ((-radius.get(0) + 1) / 2) + ((-radius.get(1) + 1) / 2) + 1, // Case 2
                            ((-radius.get(1) + 1) / 2) + ((-radius.get(2) + 1) / 2) + 2  // Case 3
                            )
                );

        System.out.println(best);
    }

    public static void main(String[] args) throws IOException{
        AdjoinNetworks adjoin = new AdjoinNetworks();
        adjoin.run();
    }
}
