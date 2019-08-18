import java.io.*;
import java.util.*;

class Triple implements Comparable<Triple>{
    int start;
    int end;
    int cost;

    public Triple(int start, int end, int cost){
        this.start = start;
        this.end = end;
        this.cost = cost;
    }

    public int compareTo(Triple other){
        return this.cost - other.cost;
    }
}

class Onion{
    private int[] onion;

    public Onion(int n){
        this.onion = new int[n];
        for (int i = 0; i < n; ++i){
            this.onion[i] = i;
        }
    }

    private int find(int x){
        if (this.onion[x] != x){
            this.onion[x] = find(this.onion[x]);
        }
        return this.onion[x];
    }

    // Check to see if two given gridtiles have been connected
    public boolean check(int x, int y){
        return find(this.onion[x]) == find(this.onion[y]);
    }

    public boolean union(int x, int y){
        int parentx = find(x);
        int parenty = find(y);

        if (parentx != parenty){
            this.onion[parentx] = parenty;
            return true;
        }
        return false;
    }
}

public class MuddyHike{
    int rows;
    int cols;
    int[][] grid;

    int[] dr = new int[5];
    ArrayList<Triple> edgeList = new ArrayList<>();

    // Private method for the Onion
    private int getIndex(int row, int col){
        return row*cols + col;
    }

    private void run() throws IOException{
        // Shit I can't remember how to initialize an array in java!
        this.dr[0] = 0;
        this.dr[1] = 1;
        this.dr[2] = 0;
        this.dr[3] = -1;
        this.dr[4] = 0;

        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        this.rows = Integer.parseInt(dlist[0]);
        this.cols = Integer.parseInt(dlist[1]);
        grid = new int[rows][cols];

        // Initilize the index number of the superSource and superSink
        int superSource = rows*cols;
        int superSink = rows*cols + 1;

        // Initialise the onion
        Onion onion = new Onion(rows*cols + 2);

        // Scan in the board
        for (int i = 0; i < rows; ++i){
            dlist = r.readLine().split(" ");
            for (int j = 0; j < cols; ++j){
                int cost = Integer.parseInt(dlist[j]);
                grid[i][j] = cost;
            }
        }

        // Create the graph
        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j){
                int currIndex = getIndex(i, j);
                int currCost = grid[i][j];

                for (int k = 0; k < 4; ++k){
                    int newRow = i+dr[k];
                    int newCol = j+dr[k+1];

                    // Bounds checking
                    if (newRow < 0 || newCol < 0 || newRow >= rows || newCol >= cols) continue;
                    int newIndex = getIndex(newRow, newCol);
                    int newCost = grid[newRow][newCol];

                    // Connect the stuff
                    edgeList.add(new Triple(currIndex, newIndex, Math.max(currCost, newCost)));
                }
            }
        }

        // Connect the left half of the graph to the supersource;
        // Connect the right half of the graph to the supersink;
        for (int i = 0; i < rows; ++i){
            edgeList.add(new Triple(getIndex(i, 0), superSource, grid[i][0]));
            edgeList.add(new Triple(getIndex(i, cols-1), superSink, grid[i][cols-1]));
        }

        // Sort the edgelist
        Collections.sort(edgeList);

        // Do a Kruskal's
        // Stop when we have connected the super source to the supersink!
        // And we are sure that this loop will terminate without AIOOB because
        int curr = 0;
        int currCost;
        while (true){
            Triple currentTriple = edgeList.get(curr);
            currCost = currentTriple.cost;

            // Bad design. Plane coding. Sorry.
            while (curr < edgeList.size()){
                Triple nextTriple = edgeList.get(curr);
                int nextCost = nextTriple.cost;

                // If the cost has changed, break out of the loop
                if (nextCost != currCost) break;

                // If not, union the two nodes
                onion.union(nextTriple.start, nextTriple.end);

                // Increment curr
                ++curr;
            }

            // OK we are out of the while loop, which means we reached a place where
            // we have unioned everything with some current cost.
            // Check if we have onion'ed the supersource and super sink
            if (onion.check(superSource, superSink)){

                // If we have, just print out the current cost.
                System.out.println(currCost);
                return;
            }
        }
    }

    public static void main(String[] args) throws IOException{
        MuddyHike muddyhike = new MuddyHike();
        muddyhike.run();
    }
}
