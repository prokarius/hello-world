import java.io.*;
import java.util.*;

class FenwickTree {
    int size;
    long[] fenwick;

    public FenwickTree(int n){
        this.size = n+1;
        fenwick = new long[n+1];
    }

    private int LSOne(int n){
        return n&(-n);
    }

    public void update(int location, int value){
        for (int i = location; i < this.size; i += LSOne(i)){
            fenwick[i] += value;
        }
    }

    public long rsq(int end){
        if (end == 0) return 0;

        long sum = 0;
        for (int i = end; i > 0; i-=LSOne(i)){
            sum += fenwick[i];
        }
        return sum;
    }

    public long rsq(int start, int end){
        return rsq(end) - rsq(start-1);
    }
}

public class JustForSidekicks{

    int[] values = new int[7];
    int[] gemTypes;
    FenwickTree[] fenwicks = new FenwickTree[7];

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int q = Integer.parseInt(dlist[1]);

        // Gem values
        dlist = r.readLine().split(" ");
        for (int i = 1; i <= 6; ++i){
            values[i] = Integer.parseInt(dlist[i-1]);
            fenwicks[i] = new FenwickTree(n+1);
        }

        // Gemtypes
        gemTypes = new int[n+1];
        String gemlist = r.readLine();
        for (int i = 1; i <= n; ++i){
            int type = gemlist.charAt(i-1) - '0';
            gemTypes[i] = type;
            fenwicks[type].update(i, 1);
        }

        // Queries
        for (int i = 0; i < q; ++i){
            dlist = r.readLine().split(" ");
            int queryType = Integer.parseInt(dlist[0]);
            switch (queryType){

                // Switch gem types
                case (1):
                    // Update the gem type listing
                    int gemNum = Integer.parseInt(dlist[1]);
                    int newType = Integer.parseInt(dlist[2]);
                    int oldType = gemTypes[gemNum];
                    gemTypes[gemNum] = newType;

                    // Update the fenwick tree
                    fenwicks[newType].update(gemNum, 1);
                    fenwicks[oldType].update(gemNum, -1);
                    break;

                // Switch gem values
                case (2):
                    int gem = Integer.parseInt(dlist[1]);
                    int newValue = Integer.parseInt(dlist[2]);

                    // Update the value of the gems
                    values[gem] = newValue;
                    break;

                // Get total value
                case (3):
                    int left = Integer.parseInt(dlist[1]);
                    int right = Integer.parseInt(dlist[2]);

                    // Find how many gems of each type between L and R
                    // Multiply that number by the value of each gemType
                    long out = 0;
                    for (int j = 1; j <= 6; ++j){
                        out += values[j] * fenwicks[j].rsq(left, right);
                    }

                    log.write(String.valueOf(out).getBytes());
                    log.write('\n');
                    break;
            }
        }

        log.flush();
    }

    public static void main(String[] args) throws IOException{
        JustForSidekicks sidekicks = new JustForSidekicks();
        sidekicks.run();
    }
}

