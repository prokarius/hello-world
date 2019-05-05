import java.util.*;
import java.io.*;

public class DanceRecital{
    int R; // number of routines
    int best = 1<<30; // Best cost

    // Keep the list of routines
    // Also keep the cost of the 
    String[] recitals = new String[15];
    int[][] cost = new int[15][15];

    // We need to keep track of the bitmask that we
    boolean[] visited = new boolean[15];

    // Calculates the cost between the ath and bth string
    private int calculateCost(int a, int b){
        int count = 0;
        for (int i = 0; i < recitals[a].length(); ++i){
            for (int j = 0; j < recitals[b].length(); ++j){
                if (recitals[a].charAt(i) == recitals[b].charAt(j)){
                    count++;
                }
            }
        }
        return count;
    }

    private void recurse(int curr, int currRoutines, int currentCost){
        // Have we visited all possible states?
        if (currRoutines == R){
            if (currentCost < best){
                best = currentCost;
            }
            return;
        }

        // Now we try all possible routines to see what follows the current
        for (int i = 0; i < R; ++i){
            // If we have done the routine before, give up
            // If considering this routine will never beat best, give up.
            if (visited[i]) continue;
            if (currentCost + cost[i][curr] >= best) continue;

            // Set the current visited to true and find cost. Then recurse
            visited[i] = true;
            recurse(i, currRoutines + 1, currentCost + cost[i][curr]);

            // Reset the visited array
            visited[i] = false;
        }
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 

        // Scan in input
        R = Integer.parseInt(r.readLine());
        for (int i = 0; i < R; ++i){
            recitals[i] = r.readLine();
        }

        // Calculate the pairwise cost between all recitals
        for (int i = 0; i < R; ++i){
            for (int j = 0; j < R; ++j){
                cost[i][j] = calculateCost(i, j);
            }
        }

        // We will be doing recursive backtracing:
        // Start from all possible starts
        for (int i = 0; i < R; ++i){
            visited[i] = true;
            recurse(i, 1, 0);
            visited[i] = false;
        }

        System.out.println(best);
    }

    public static void main(String[] args) throws IOException{
        DanceRecital solution = new DanceRecital();
        solution.run();
    }
}
