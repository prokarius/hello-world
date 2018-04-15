import java.util.*;
import java.io.*;

public class FeastForCats{
    int[][] adjmatrix;
    int[] distance;
    boolean[] visited;
    int out;
    public void run(BufferedReader r) throws IOException{
        // Scan in input
        String[] mandc = r.readLine().split(" ");
        int m = Integer.parseInt(mandc[0]);
        int c = Integer.parseInt(mandc[1]);
        int CX = (c*(c-1))/2;

        // Create the dp stuffs
        adjmatrix = new int[c][c];
        distance = new int[c];
        visited = new boolean[c];
        out = 0;

        for (int i=0; i<CX; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            int weight = Integer.parseInt(dlist[2]);
            adjmatrix[start][end] = weight;
            adjmatrix[end][start] = weight;
        }

        // Initialise the original distance to the connections of vertex 0
        // We artbitrarily selected node 0 to be our initial node
        for (int i=1; i<c; ++i){
            distance[i] = adjmatrix[0][i];
        }
        visited[0] = true;

        // Then for c-1 more times, find the smallest node to add to the MST.
        for (int i=1; i<c; ++i){

            // Set the distance to INF first.
            int best = 2000000000;
            int vertextoadd = -1;

            // Look through the distance to the next vertice, and find the least
            // But only if we have not visited it before.
            for (int j=0; j<c; ++j){
                if (!visited[j] && best > distance[j]){
                    best = distance[j];
                    vertextoadd = j;
                }
            }

            // Now vertextoadd is the index of the next vertex to add
            // That and best is the lowest distance.
            out += best;

            for (int j=0; j<c; ++j){
                if (distance[j] > adjmatrix[vertextoadd][j]){
                    distance[j] = adjmatrix[vertextoadd][j];
                }
            }

            // Then set vertextoadd to be true
            visited[vertextoadd] = true;
        }

        // Check the total cost. Don't forget to subtract 1 for each cat to drink.
        System.out.println(m-c >= out ? "yes" : "no");
    }

    public static void main(String[] args) throws IOException{
        FeastForCats solution = new FeastForCats();

        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());
        while (testcases > 0){
            solution.run(r);
            testcases--;
        }
    }
}
