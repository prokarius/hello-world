import java.util.*;

// Union Find Disjoint Set class
class Onion{
    private int[] onion;

    // Set up the onion
    public Onion(int n){
        onion = new int[n];
        for (int i=0; i<n; ++i){
            this.onion[i] = i;
        }
    }

    public int find(int a){
        if (this.onion[a] != a){
            this.onion[a] = find(this.onion[a]);
        }
        return this.onion[a];
    }

    public void union(int a, int b){
        int x = this.find(a);
        int y = this.find(b);
        onion[x] = y;
    }

    public boolean sameSet(int a, int b){
        return (this.find(a) == this.find(b));
    }
}

public class Kastenlauf{
    private boolean checkdistance(int x1, int x2, int y1, int y2, int threshold){
        return threshold >= (Math.abs(x1 - x2) + Math.abs(y1 - y2));
    }

    public void run(int n, Scanner s){
        // Scan in input
        int[][] dlist = new int[n][2];
        Onion ufds = new Onion(n);
        for (int i=0; i<n; ++i){
            int x = s.nextInt();
            int y = s.nextInt();
            dlist[i][0] = x;
            dlist[i][1] = y;
        }

        // For each element in the dlist, if the manhatten distance is close
        // enough, onion the two vertices together
        for (int i=1; i<n; ++i){
            for (int j=0; j<i; ++j){
                if (checkdistance(dlist[i][0], dlist[j][0], dlist[i][1], dlist[j][1], 1000)){
                    ufds.union(i, j);

                    // If at any time the start and end are onioned
                    // Then just return happy
                    if (ufds.sameSet(0, n-1)){
                        System.out.println("happy");
                        return;
                    }
                }
            }
        }

        // If the thing cannot link start to end, then we just print sad.
        System.out.println("sad");
    }

    public static void main(String[] args){
        Kastenlauf solution = new Kastenlauf();
        Scanner s = new Scanner(System.in);
        int testcases = s.nextInt();
        while (testcases > 0){
            int n = s.nextInt();
            solution.run(n+2, s);
            testcases--;
        }
    }
}
