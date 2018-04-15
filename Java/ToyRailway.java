import java.util.*;
import java.io.*;

public class ToyRailway{
    private static int tokenToVertex(String string){
        char[] charray = string.toCharArray();
        int number = 0;
        int len = string.length()-1;

        // Modify the number
        for (int i=0; i<len; ++i){
            number = number * 10 + charray[i] - '0';
        }

        // Then add on the last character
        return number*3 + (charray[len] - 'A');
    }

    private void run() throws IOException{
        // Scan in input

        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] nandm = r.readLine().split(" ");
        int n = Integer.parseInt(nandm[0]);
        int m = Integer.parseInt(nandm[1]);

        // We will set up the adj list here:
        // Note that there can only be at most 2 connections, so we initialise a
        // 2D adjlist. adjlist[0] will contain the number of connections
        int[][] adjlist = new int[3+3*n][3];

        // For each connection find who it connects to
        // Oh also we subtract 3 because of one based numbering
        for (int i=0; i<m; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = tokenToVertex(dlist[0]);
            int end = tokenToVertex(dlist[1]);

            // Wait, but if end is going to vertex A
            // it should be pointing at vertices B and C
            // this is where the DFS magic happens
            if (end % 3 == 0){
                // But if it is node 1A, make it go to node 2.
                if (end == 3){
                    adjlist[start][0] = 1;
                    adjlist[start][1] = 2;
                }
                else {
                    adjlist[start][0] = 2;
                    adjlist[start][1] = end+1;
                    adjlist[start][2] = end+2;
                }
            }

            // Well if not, its going to vertex B or C
            // Then route it to A
            else { // (end % 3 == 1) || (end % 3 == 2)
                adjlist[start][0] = 1;
                adjlist[start][1] = end - (end%3);
            }

            // Don't forget this shit goes both ways:
            if (start % 3 == 0){
                if (start == 3){
                    adjlist[end][0] = 1;
                    adjlist[end][1] = 2;
                }
                else {
                    adjlist[end][0] = 2;
                    adjlist[end][1] = start+1;
                    adjlist[end][2] = start+2;
                }
            }

            else { // (start % 3 == 1) || (start % 3 == 2)
                adjlist[end][0] = 1;
                adjlist[end][1] = start - (start % 3);
            }
        }

        // Great the input has been scanned!
        // Now we just want to BFS from vertex 1B and 1C. Which is...
        // 1*3 + 1 (2) = vertex 4 (5). Lovely.
        LinkedList<Integer> bfsqueue = new LinkedList<>();
        bfsqueue.addFirst(4);
        bfsqueue.addFirst(5);

        // OK when we pop the guy, we will set the vertex's parent
        // Then when we check the parent, we can see which vertices have been
        // visited before
        int[] parent = new int[3+3*n];
        while (!bfsqueue.isEmpty()){
            int curr = bfsqueue.pollLast();
            // Check if we returned to the start!
            if (curr == 2){
                break;
            }

            // For each of the neighbours
            for (int i=1; i<=adjlist[curr][0]; ++i){

                // Check if we have visited it before. Push if we haven't
                if (parent[adjlist[curr][i]] == 0){
                    bfsqueue.addFirst(adjlist[curr][i]);
                    parent[adjlist[curr][i]] = curr;
                }
            }
        }

        // Lets deal with whether it's impossible first:
        // If when we get here, the parent of curr is still 0, then mampus
        if (parent[2] == 0){
            System.out.println("Impossible");
            return;
        }

        // OK we established it's possible.
        char[] output = new char[n+1];

        // We just need to see which switches go where.
        // Start from the parent of 3.
        int trail = parent[2];

        // Now, while we are not back where we came from, we see how we got
        // there. Note that the direction of the switch is given by the station
        // we currently are at, whether it's 1 or 2 mod 3.
        // If trail % 3 = 0, that means we entered from either B or C. Ignore.
        while (trail != 0){
            if (trail % 3 != 0){
                // Now we established from here we came from a vertex A.
                // The train station in question is given by trail/3
                // The direction the switch should be set is given by the mod.
                output[trail/3] = (char) (trail%3 + 'A');
            }

            // Then continue the trail
            trail = parent[trail];
        }

        // OK last bit: The printing. Lets get out our favourite OutputStream
        OutputStream log = new BufferedOutputStream (System.out);

        // For each character, if it's not defined yet (null byte), arbitrarily
        // write a B
        for (int i=1; i<=n; ++i){
            if (output[i] == '\0'){
                log.write('B');
            }
            else {
                log.write(output[i]);
            }
            log.flush();
        }

        // Add the newline and print!
        log.write('\n');
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        ToyRailway toyrail = new ToyRailway();
        toyrail.run();
    }
}
