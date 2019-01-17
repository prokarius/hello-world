import java.io.*;
import java.util.*;

public class BirthdayParty{
    private int numVertices;
    private int numEdges;
    private ArrayList<ArrayList<Integer>> adjlist;
    private int count;
    private int[] dfsnum;
    private int[] dfslow;
    private int[] parent;

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
        dfsnum = new int[vertices];
        dfslow = new int[vertices];
        parent = new int[vertices];
        count = 1;
    }

    // So that we handle all the IO stuff in main method
    private void addEdge(int x, int y){
        adjlist.get(x).add(y);
        adjlist.get(y).add(x);
    }

    // This is so that we can do dfs downwards
    private void dfs(int node){

        // Visit ALL the nodes!
        dfsnum[node] = count;
        dfslow[node] = count++;

        for (int neighbour : adjlist.get(node)){
            // Check if we have visited it before
            if (dfsnum[neighbour] != 0){
                if (parent[node] == neighbour) continue;
                dfslow[node] = Math.min(dfslow[node], dfslow[neighbour]);
            }
            else {
                parent[neighbour] = node;
                dfs(neighbour);
                dfslow[node] = Math.min(dfslow[node], dfslow[neighbour]);
            }
        }
    }

    // Run the main solver!
    private void run(BufferedReader r) throws IOException{
        // Pick an arbitrary node to start DFSing
        // Lets pick node 0.
        dfs(0);

        // Check for each edge from u to v
        // If dfslo[v] > dfsnum[u] => Bridge
        for (int start = 0; start < adjlist.size(); ++start){
            for (int neighbour : adjlist.get(start)){
                if (dfslow[neighbour] > dfsnum[start]){
                    System.out.println("Yes");
                    return;
                }
            }
        }
        // If a vertex is not visited, print yet
        if (count != adjlist.size() + 1) System.out.println("Yes");
        else System.out.println("No");
    }


    public static void main(String[] args) throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int vertices = Integer.parseInt(dlist[0]);
        int edges = Integer.parseInt(dlist[1]);

        // Guaranteed >1 vertex
        while (vertices != 0){
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
