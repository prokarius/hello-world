import java.util.*;
import java.io.*;

// This is similar to magical GCDs
public class VolumeAmplify{
    public void run(BufferedReader r) throws IOException{
        // Scan in input
        HashSet<Integer> hashset = new HashSet<>();
        HashSet<Integer> tempset = new HashSet<>();
        String[] aandy = r.readLine().split(" ");
        int a = Integer.parseInt(aandy[0]);
        int y = Integer.parseInt(aandy[1]);

        // Create the list of amplifiers and read into it
        int[] amplifiers = new int[a];
        String[] dlist = r.readLine().split(" ");
        for (int i=0; i<a; ++i){
            amplifiers[i] = Integer.parseInt(dlist[i]);
        }

        // Create the two hashsets and push number 1 into hashset 1.
        // The number 1 acts as our original volume level
        hashset.add(1);

        // For each amplifier
        for (int i=0; i<a; ++i){
            int curr = amplifiers[i];

            // Reset the tempset we are pushing into
            tempset.clear();

            // As well, try to multiply the item by curr.
            // Push it in only if it doesn't exceed y
            for (int prev : hashset){
                if (curr * prev < y){
                    tempset.add(curr*prev);
                }
                else if (curr * prev == y){
                    System.out.println(y);
                    return;
                }
            }

            // Then push all the stuff from tempset into our hashset
            for (int item : tempset){
                hashset.add(item);
            }
        }

        int best = 1;
        // Now, find the largest items in the hashset.
        for (int item : hashset){
            best = (best > item) ? (best) : (item);
        }

        System.out.println(best);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        VolumeAmplify solution = new VolumeAmplify();
        int testcases = Integer.parseInt(r.readLine());
        while (testcases > 0){
            solution.run(r);
            --testcases;
        }
    }
}
