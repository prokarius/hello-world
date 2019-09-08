import java.io.*;
import java.util.*;

class Edge{
    int start;
    int end;
    double flow;
    boolean power;

    public Edge(int start, int end, int flow, int power){
        this.start = start;
        this.end = end;
        this.flow = flow / 100.0;
        this.power = (power == 1);
    }
}

public class Mravi{
    // Is this how you #define in java??
    private final double EPSILON = 1e-6;

    ArrayList<ArrayList<Edge>> adjList = new ArrayList<>();
    double[] required;

    // Returns true if this node, and the nodes below it can be satisfied
    // Recursively does dfs to check all the nodes
    private boolean check(int curr, double drip, int parent){
        // Are we at a leaf node?
        // Does it have the correct amount of drip?
        if (required[curr] > 0 && drip < required[curr]) return false;

        // For each of the neighbours, drip into it
        // Unless we just came from there, then don't even bother
        for (Edge neighbour : adjList.get(curr)){
            int next = neighbour.end;
            if (next == parent) continue;

            double newDrip = drip * neighbour.flow;

            // Does this pipe get SUPERPOWERS?
            if (neighbour.power){

                // AHA! If the amount of drip is between 0 - 1, squaring the amount
                // of drip actually makes it less! Naughty naughty
                if (newDrip > 1){
                    newDrip = newDrip * newDrip;
                }
            }

            // FLOW INTO THE NEXT PIPE!
            if (!check(next, newDrip, curr)){
                return false;
            }
        }

        return true;
    }


    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());

        // Populate the adjList
        for (int i = 0; i <= n; ++i){
            adjList.add(new ArrayList<>());
        }

        // Scan in the Edges
        for (int i = 1; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            int flow = Integer.parseInt(dlist[2]);
            int power = Integer.parseInt(dlist[3]);

            // Tbh we can do a traversal from node 1 to see what the flow path is
            // since this is a tree, but I'm a bit lazy to implement
            adjList.get(start).add(new Edge(start, end, flow, power));
            adjList.get(end).add(new Edge(end, start, flow, power));
        }

        // Lastly, scan in the amount of drip needed
        required = new double[1+n];
        String[] dlist = r.readLine().split(" ");
        for (int i = 1; i <= n; ++i){
            required[i] = Double.parseDouble(dlist[i-1]);
        }

        // Now do a binary search!
        double hi = 1e10;
        double lo = 0;

        while (hi - lo > EPSILON){
            double mid = lo + (hi - lo)/2;
            if (check(1, mid, -1)) hi = mid;
            else lo = mid;
        }

        // Print that shit
        System.out.printf("%.9f\n", (hi + lo)/2);
    }

    public static void main(String[] args) throws IOException{
        Mravi mravi = new Mravi();
        mravi.run();
    }
}

