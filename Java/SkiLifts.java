import java.io.*;
import java.util.*;

public class SkiLifts {
    int[][] liftCounts = new int[100005][2];

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        int n = Integer.parseInt(r.readLine());

        //  Count the number of lifts of each type at each level
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int y = Integer.parseInt(dlist[1]);
            int a = Integer.parseInt(dlist[2]);

            liftCounts[y][a-1]++;
        }
        
        // Greedy. Get rid of all the one way pylons first though
        int out = 0;

        for (int i = 0; i < 100000; ++i){
            // At y=i, how many pylons are left?
            int pylonsLeft = liftCounts[i][0] + liftCounts[i][1];

            // How many 2 way pylons can we fit at y=i+1?
            int used = Math.min(pylonsLeft, liftCounts[i+1][1]);
            out += used;
            pylonsLeft -= used;

            // If we need to connect to 1 way pylons at y=i+1, remove the 1 way pylons
            if (used == liftCounts[i+1][1]){
                used = Math.min(pylonsLeft, liftCounts[i+1][0]);
                out += used;
                liftCounts[i+1][0] -= used;
            }
        }

        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        SkiLifts skiLift = new SkiLifts();
        skiLift.run();

    }
}

