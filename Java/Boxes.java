import java.io.*;
import java.util.*;

public class Boxes{

    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    int[] starts;
    int[] ends;
    int count = 0;

    // Does a preorder traversal, and saves where the node starts and ends
    // The boxes that are contained below a given node is in [start, end]
    // Note that the position of a box is also the same as start
    private void traverse(int node){
        starts[node] = count;
        ++count;

        // Loop through all
        for (int neighbour : adjlist.get(node)){
            traverse(neighbour);
        }

        ends[node] = count;
    }

    // Returns 1 if box 2 is inside box 1
    // Returns 2 is box 1 is inside box 2
    private int containsBox(int box1, int box2){
        if (starts[box1] < ends[box2] && starts[box1] > starts[box2]) return 2;
        if (starts[box2] < ends[box1] && starts[box2] > starts[box1]) return 1;
        return 0;
    }

    private int numBoxes(int box){
        return ends[box] - starts[box];
    }

    private void solve(BufferedReader r, OutputStream log) throws IOException{
        boolean[] toQuery = new boolean[24];
        int[] boxes = new int[24];

        String[] dlist = r.readLine().split(" ");
        int numBoxes = Integer.parseInt(dlist[0]);

        // Parse the boxes
        for (int i = 1; i <= numBoxes; ++i){
            boxes[i] = Integer.parseInt(dlist[i]);
            toQuery[i] = true;
        }

        // For each of the boxes, check to see if they are entirely contained within
        // the other.
        for (int i = 1; i < numBoxes; ++i){
            for (int j = i+1; j <= numBoxes; ++j){
                int replace = containsBox(boxes[i], boxes[j]);
                if (replace == 1){
                    toQuery[j] = false;
                }
                else if (replace == 2){
                    toQuery[i] = false;
                }
            }
        }

        // Sum up all the boxes
        int output = 0;
        for (int i = 1; i <= numBoxes; ++i){
            if (toQuery[i]){
                output += numBoxes(boxes[i]);
            }
        }

        // Write to the logger and print
        log.write(String.valueOf(output).getBytes());
        log.write('\n');
    }


    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        // Scan in input
        int N = Integer.parseInt(r.readLine());

        // Create the adjlist
        for (int i = 0; i <= N; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Populate the adjlist and other data structures
        String[] dlist = r.readLine().split(" ");
        for (int i = 1; i <= N; ++i){
            int parent = Integer.parseInt(dlist[i - 1]);
            adjlist.get(parent).add(i);
        }

        starts = new int[N+1];
        ends = new int[N+1];

        // Now we will do a pre-order traversal.
        // For each box, we store the range of boxes below it betwee start and end
        // We start from the super box: Box 0.
        traverse(0);

        // Cool, we now have all the info we need. Time to process some queries!
        int Q = Integer.parseInt(r.readLine());
        for (int i = 0; i < Q; ++i){
            solve(r, log);
        }

        // PRINT IT ALL OUT!!!
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        Boxes boxes = new Boxes();
        boxes.run();
    }
}
