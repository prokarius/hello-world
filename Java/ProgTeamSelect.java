import java.util.*;
import java.io.*;

public class ProgTeamSelect{
    // dpset stores all the groupings we have seen before
    HashMap<Long, Boolean> dpset = new HashMap<>();

    // Stores the adjency list
    int[][] adjlist = new int[60][60];

    // Mapping stores the mapping of names to integers
    HashMap<String, Integer> mapping = new HashMap<>();
    int numstudents = 0;

    public void run(int n, BufferedReader r) throws IOException{
        // Build the adj matrix.
        int student1, student2;
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            if (mapping.containsKey(dlist[0])){
                student1 = mapping.get(dlist[0]);
            }
            else {
                mapping.put(dlist[0], numstudents);
                student1 = numstudents++;
            }
            if (mapping.containsKey(dlist[1])){
                student2 = mapping.get(dlist[1]);
            }
            else {
                mapping.put(dlist[1], numstudents);
                student2 = numstudents++;
            }
            adjlist[student1][student2] = 1;
            adjlist[student2][student1] = 1;
        }

        // Prelim check if the number of students are divisible by 3
        if (numstudents % 3 != 0){
            System.out.println("impossible");
            return;
        }

        // Start the dp.
        if (dp((1L << numstudents) - 1)){
            System.out.println("possible");
        }
        else {
            System.out.println("impossible");
        }
    }

    // This is a top down DP
    private boolean dp(long x){
        // First check to see if x has been seen before
        if (dpset.containsKey(x)) return dpset.get(x);

        // If not, check if x is 0 already:
        if (x == 0) return true;

        dpset.put(x, false);

        // Now we find all possible triples using brute force:
        for (int i = 0; i < numstudents-2; ++i){

          // Check to see if this student is already included in the state
          // If so, don't bother, just skip the state
          if ((x & (1L << i)) == 0) continue;

            // Second guy
            for (int j = i+1; j < numstudents-1; ++j){
              if ((x & (1L << j)) == 0) continue;

              // Check to see if these two students are OK with each other
              if (adjlist[i][j] != 1) continue;

                // Third guy
                for (int k = j+1; k < numstudents; ++k){
                  if ((x & (1L << k)) == 0) continue;

                  // Check to see if the 3rd guy is OK with the first 2
                  if ((adjlist[i][k] != 1) || (adjlist[j][k] != 1)) continue;

                    // OK they are all OK with each other.
                    // Time to recurse
                    long newstate = x ^ (1L << i) ^ (1L << j) ^ (1L << k);
                    if (dp(newstate)){
                        dpset.put(x, true);
                        return true;
                    }
                }
            }
        }

        // If we reached here, too bad, there are no good triples
        return false;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        while (n != 0){
            ProgTeamSelect solution = new ProgTeamSelect();
            solution.run(n, r);
            n = Integer.parseInt(r.readLine());
        }
    }
}
