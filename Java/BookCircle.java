/* TRIGGER WARNING */
/* This Solution Assumes Binary Gender */

import java.io.*;
import java.util.*;

public class BookCircle{
    // Mapping of the Book to the guy's ID
    HashMap<String, Integer> mapping = new HashMap<>();
    ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();
    int[] forwardConnection;
    int[] backwardConnection;
    boolean[] visited;

    private boolean dfs(int boy){
        if (visited[boy]) return false;
        visited[boy] = true;

        for (int girl : adjList.get(boy)){
            if (backwardConnection[girl] == -1 || dfs(backwardConnection[girl])){
                backwardConnection[girl] = boy;
                forwardConnection[boy] = girl;
                return true;
            }
        }

        // If we reached here, we have failed to find a augmenting path
        return false;
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int numBoys = Integer.parseInt(dlist[0]);
        int numGirls = Integer.parseInt(dlist[1]);

        // Initialise my adjList
        for (int boy = 0; boy < numBoys ; ++boy){
            adjList.add(new ArrayList<>());
        }

        // Map each book the boy has read into his own mapping.
        for (int boy = 0; boy < numBoys; ++boy){
            dlist = r.readLine().split(" ");
            for (int book = 2; book < dlist.length; ++book){
                mapping.put(dlist[book], boy);
            }
        }

        forwardConnection = new int[numBoys];
        backwardConnection = new int[numGirls];
        visited = new boolean[numGirls];

        // For each book the girl has read, find the matching guy who read the book before
        for (int girl = 0; girl < numGirls; ++girl){
            dlist = r.readLine().split(" ");
            for (int book = 2; book < dlist.length; ++book){
                int boy = mapping.get(dlist[book]);
                adjList.get(boy).add(girl);
            }
        }

        int out = 0;

        // Initialise the connections
        for (int boy = 0; boy < numBoys; ++boy){
            forwardConnection[boy] = -1;
        }

        for (int girl = 0; girl < numGirls; ++girl){
            backwardConnection[girl] = -1;
        }

        // Now it's time to find the Maximum Cardinality Bipartite Matching
        // Initialise the forward and backward edges
        for (int boy = 0; boy < numBoys; ++boy){
            for (int girl : adjList.get(boy)){
                if (backwardConnection[girl] != -1) continue;
                forwardConnection[boy] = girl;
                backwardConnection[girl] = boy;
                out++;
                break;
            }
        }

        // We will check each boy if we can make a match
        for (int boy = 0; boy < numBoys; ++boy){
            if (forwardConnection[boy] != -1) continue;
            visited = new boolean[numBoys];
            if (dfs(boy)) out++;
        }

        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        BookCircle bookCircle = new BookCircle();
        bookCircle.run();
    }
}
