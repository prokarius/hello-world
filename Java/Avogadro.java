import java.util.*;
import java.io.*;

public class Avogadro{
    static boolean[] deleted = new boolean[100005]; // Deleted columns
    static int[][] arr = new int[3][100005]; // Input table
    static int[][] instance = new int[3][100005]; // Stores #instances in each row
    static ArrayList<HashSet<Integer>> vecset = new ArrayList<>();
    static Set<Integer> output = new HashSet<>(); // Stores cols we deleted
    static Set<Integer> toDelete = new HashSet<>(); // Stores cols we want to delete
    public static void main(String[] arg){
        try{
            // Scan in input using Buffered Reader
            BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
            int n = Integer.parseInt(r.readLine());

            // Set up the vecset thing, stores col number of each number
            // Set up the deleted columns thing
            for (int i=0; i<100005; i++){
                vecset.add(new HashSet<Integer>());
                deleted[i] = false;
            }

            // For each entry, store in arr, and track the cols it appears in
            // Also take note of the number of instances of each number
            for (int i=0; i<3; ++i){
                String[] ph = r.readLine().split(" ");
                for (int j=0; j<n; ++j){
                    int k = Integer.parseInt(ph[j]);
                    arr[i][j] = k;
                    vecset.get(k).add(j);
                }
            }

            // Keep track of #instances of each number left in each row
            for (int i=0; i<3; i++){
                for (int j=0; j<n; j++) instance[i][arr[i][j]]++;
            }

            // Create a set toDelete which will contain numbers to delete
            for (int i=0; i<3; i++){
                for (int j=0; j<=n; j++){
                    if (instance[i][j] == 0) toDelete.add(j);
                }
            }

            // while toDelete has numbers in it, delete numbers
            while (toDelete.size() > 0){
            // For each column Q which N appears in:
                int N = toDelete.iterator().next();
                toDelete.remove(N);
                for (int Q : vecset.get(N)){
                    // if not already in output, add them in
                    if (!deleted[Q]){
                        output.add(Q);
                        deleted[Q] = true;
                        // for the numbers M in the Q three rows:
                        // reduce their #instances by 1 and check if it's 0
                        for (int i=0; i<3; ++i){
                            int M = arr[i][Q];
                            --instance[i][M];
                            if (instance[i][M] == 0) toDelete.add(M);
                        }
                    }
                }
            }

            System.out.printf("%d\n", output.size());
        }
        catch (IOException e){}
    }
}
