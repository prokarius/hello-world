import java.io.*;
import java.util.*;

public class BirthdayParty{
    private int numVertices;
    private int numEdges;
    private ArrayList<ArrayList<Integer>> adjlist;
    private int[] distanceEstimate;
    private int[] distanceClosest;

    // PRIVATE Constructor so that I can set up everything one shot
    private BirthdayParty(int vertices, int edges){
        numVertices = vertices;
        numEdges = edges;

        // Initialise our adjlist
        adjlist = new ArrayList<>();
        for (int i = 0; i < vertices; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Initialise our initial distance estimate.
        // As well as the lowest number next to each vertex.
        distanceEstimate = new int[vertices];
        distanceClosest = new int[vertices];
    }

    // So that we handle all the IO stuff in main method
    private void addEdge(int x, int y){
        adjlist.get(x).add(y);
        adjlist.get(y).add(x);
    }

    // This is so that we can do dfs downwards
    private void dfs(){
        

    }

    // Run the main solver!
    private void run(BufferedReader r) throws IOException{
        // Pick an arbitrary node to start DFSing
        // Lets up pick node 0.
        dfs();
    }


    public static void main(String[] args) throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int vertices = Integer.parseInt(dlist[0]);
        int edges = Integer.parseInt(dlist[1]);

        // Guaranteed >1 vertex
        while (vertices == 0){
            BirthdayParty solution = new BirthdayParty(vertices, edges);

            // Input the array
            for (int i = 0; i < edges; ++i){
                dlist = r.readLine().split(" ");
                int x = Integer.parseInt(dlist[0]);
                int y = Integer.parseInt(dlist[1]);
                solution.addEdge(x, y);
            }

            // Run the solution
            solution.run(r);
            dlist = r.readLine().split(" ");
            vertices = Integer.parseInt(dlist[0]);
            edges = Integer.parseInt(dlist[1]);
        }
    }
}
