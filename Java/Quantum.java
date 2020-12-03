import java.io.*;
import java.util.*;

class Transform{
    // Extract these away so that we can easily apply
    int andMask; // Bit will be 0 for C (Clear) bits, 1 otherwise
    int orMask;  // Bit will be 1 for S (Set) bits, 0 otherwise
    int xorMask; // Bit will be 1 for F (Flip) bits, 0 otherwise
    int cost;

    // Constructor that takes a string and converts it into the correct mask
    public Transform(String str, int cost){
        this.cost = cost;

        // Find the masks that will be used
        this.andMask = 0;
        this.orMask = 0;
        this.xorMask = 0;

        for (int i = 0; i < str.length(); ++i){
            char operation = str.charAt(i);

            // Switch statements!
            switch (operation){
                case 'N':
                    this.andMask = (this.andMask << 1) + 1;
                    this.orMask = (this.orMask << 1);
                    this.xorMask = (this.xorMask << 1);
                    break;
                case 'C':
                    this.andMask = (this.andMask << 1);
                    this.orMask = (this.orMask << 1);
                    this.xorMask = (this.xorMask << 1);
                    break;
                case 'S':
                    this.andMask = (this.andMask << 1) + 1;
                    this.orMask = (this.orMask << 1) + 1;
                    this.xorMask = (this.xorMask << 1);
                    break;
                case 'F':
                    this.andMask = (this.andMask << 1) + 1;
                    this.orMask = (this.orMask << 1);
                    this.xorMask = (this.xorMask << 1) + 1;
                    break;
            }
        }
    }

    // Takes an integer and transforms it
    public int transform(int input){
        return ((input & andMask) | orMask) ^ xorMask;
    }
}

class Pair implements Comparable<Pair>{
    int curr;
    int cost;

    public Pair(int curr, int cost){
        this.curr = curr;
        this.cost = cost;
    }

    public int compareTo(Pair other){
        return this.cost - other.cost;
    }
}

public class Quantum{
    // Returns the decimal value of the input string
    private int binToDec(String str){
        int output = 0;
        for (int i = 0; i < str.length(); ++i){
            output = output * 2 + str.charAt(i) - '0';
        }
        return output;
    }

    Transform[] transforms; // Stores all the transforms available
    PriorityQueue<Pair> dijkstra = new PriorityQueue<>();
    int[] dp;

    // Returns the smallest cost from start to end
    // Or returns -1 if it is not possible
    private int doDijkstra(int start, int end){
        // Reset the visited / dp array
        dp = new int[1 << l];
        dijkstra = new PriorityQueue<>();

        // Initial seed
        dijkstra.add(new Pair(start, 1<<31));

        // Have we reached the end?
        while (!dijkstra.isEmpty()){
            // Pop the top element
            Pair currPair =  dijkstra.poll();

            int curr = currPair.curr;
            int cost = currPair.cost;

            // Have we reached the end
            if (curr == end){
                return cost;
            }

            // If not have we seen this node and is better before?
            if (dp[curr] < cost) continue;

            // OK we will need to visit all of this guy's friends
            for (int i = 0; i < nop; ++i){
                int next = transforms[i].transform(curr);
                int newCost = cost + transforms[i].cost;

                // But there is no point if we already have something better
                if (dp[next] <= newCost) continue;

                // Else, put the new guy into the dp map, and add to the PQ
                dp[next] = newCost;
                dijkstra.add(new Pair(next, newCost));
            }
        }
        // Oh. We have reached the end without finding the best. Bummer.
        return 1000000007;
    }

    int l, nop, nw;

    private void run(BufferedReader r, OutputStream log) throws IOException{
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        l = Integer.parseInt(dlist[0]);
        nop = Integer.parseInt(dlist[1]);
        nw = Integer.parseInt(dlist[2]);

        transforms = new Transform[nop];

        // Scan in the transformations
        for (int i = 0; i < nop; ++i){
            dlist = r.readLine().split(" ");
            transforms[i] = new Transform(dlist[0], Integer.parseInt(dlist[1]));
        }

        // Scan in the queries
        for (int i = 0; i < nw; ++i){
            dlist = r.readLine().split(" ");
            int start = binToDec(dlist[0]);
            int end = binToDec(dlist[1]);

            // Write the space only when we are not the first element
            if (i != 0){
                log.write(' ');
            }

            int output = doDijkstra(start, end);
            if (output != 1000000007){
                log.write(String.valueOf(output - (1<<31)).getBytes());
            }
            else { // Not possible
                log.write('N');
                log.write('P');
            }
        }

        log.write('\n');
        log.flush(); // Flush that shit!
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);
        int testcases = Integer.parseInt(r.readLine());

        for (int i = 0; i < testcases; ++i){
            Quantum quantum = new Quantum();
            quantum.run(r, log);
        }

    }
}

