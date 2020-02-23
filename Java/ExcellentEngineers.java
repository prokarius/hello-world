import java.io.*;
import java.util.*;

class Engineer implements Comparable<Engineer>{
    int x;
    int y;
    int z;

    public Engineer(int x, int y, int z){
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public int compareTo(Engineer other){
        return -(this.z - other.z);
    }
}

public class ExcellentEngineers{
    private void run(BufferedReader r) throws IOException{
        // Scan in input
        int n = Integer.parseInt(r.readLine());
        Engineer[] engineers = new Engineer[n];

        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int x = 1 + n - Integer.parseInt(dlist[0]);
            int y = 1 + n - Integer.parseInt(dlist[1]);
            int z = 1 + n - Integer.parseInt(dlist[2]);
            engineers[i] = new Engineer(x, y, z);
        }

        // Sort the engineers from largest to smallest in z value
        Arrays.sort(engineers);

        int numOvershadowed = 0;

        // Walk through the list backwards in z.
        // Ensure that he isn't overshadowed by any guy.
        // We will keep a treemap that keeps track of all the Y values, sorted by X
        //   Q-----+-----+-----+
        //   |     |     |     |
        // 5 +-----X-----+-----+
        //   |  A  |     |     |
        // 2 +-----+-----Y-----+
        //   |  C  |  B  |     |
        // 0 +-----+-----+-----S
        //   0     4     6
        //
        //  In this case our TreeMap will store (SENTINEL, {4: 5}, {6, 2}, SENTINEL)
        //  Corresponding to points Q, X, Y and S respectively.

        TreeMap<Integer, Integer> ability = new TreeMap<>();
        ability.put(1<<30, -1); // Sentinel value in X axis
        ability.put(-1, 1<<30); // Sentinel value in Y axis

        for (int i = 0; i < n; ++i){
            int x = engineers[i].x;
            int y = engineers[i].y;

            // For each engineer, find what is the next highest X value in the tree
            int higherX = ability.ceilingKey(x);
            int higherY = ability.get(higherX);

            // If we are overshadowed by this guy that we just found, add one to our
            // overshadowed count and move on with life
            if (y < higherY){
                ++numOvershadowed;
                continue;
            }

            // If not, put the guy into the tree
            ability.put(x, y);

            // OK we are our own boss.
            // Check to see if our underlings are more worthless than us.
            // Keep popping underlings until we find someone better
            // +-----+-----+-----+-----+
            // |     |     |     |     |
            // +-----Y-----+-----+-----+
            // |     |     |     |     |
            // +-----+-----+-----Q-----+
            // |     |     |     |     |
            // +-----+-----X-----+-----+
            // |     |     |     |     |
            // +-----+-----+-----+-----+
            // i.e. In the situation above, when we add Q, we will pop X, but not
            // pop Y, because X is overpowered by Q

            int nextLowerX = x;
            while (true){
                nextLowerX = ability.floorKey(nextLowerX-1);
                if (ability.get(nextLowerX) > y) break;
                ability.remove(nextLowerX);
            }
        }

        // Now that everything is done, print that shit and move on
        System.out.println(n - numOvershadowed);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());
        while (testcases-- > 0){
            ExcellentEngineers engineers = new ExcellentEngineers();
            engineers.run(r);
        }
    }
}

