import java.io.*;
import java.util.*;

public class Absurdistan3{
    ArrayList<HashSet<Integer>> adjlist = new ArrayList<>();

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        // Scan in input
        int n = Integer.parseInt(r.readLine());

        // Tracks the degree of each vertex
        int[] degree = new int[n+1];

        // Track whether we have already printed the road connecting this vertex
        boolean[] visited = new boolean[n+1];

        // Initialise my adjlist
        for (int i = 0; i <= n; ++i){
            adjlist.add(new HashSet<>());
        }

        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            // Add 1 to each degree
            degree[start]++;
            degree[end]++;

            // Push into adjlist as well
            adjlist.get(start).add(end);
            adjlist.get(end).add(start);
        }

        // OK now, we loop through all the vertices to find who has degree 1
        // We add them to a LinkedList. Lets make it a LIFO.
        LinkedList<Integer> queue = new LinkedList<>();
        for (int i = 1; i <= n; ++i){
            if (degree[i] == 1){
                queue.addFirst(i);
            }
        }

        while (!queue.isEmpty()){
            int curr = queue.pollLast();
            int currEnd = adjlist.get(curr).toArray(new Integer[2])[0];
            log.write(String.valueOf(curr).getBytes());
            log.write(' ');
            log.write(String.valueOf(currEnd).getBytes());
            log.write('\n');

            degree[curr]--;
            degree[currEnd]--;

            // Mark that we have visited curr
            visited[curr] = true;

            // Remove the edge
            adjlist.get(currEnd).remove(curr);

            // If this causes currEnd to have only 1 degree, then add currEnd to the
            // queue as well~!
            if (degree[currEnd] == 1){
                queue.addFirst(currEnd);
            }
        }

        // When we are here, we are left with cycles.
        for (int i = 1; i <= n; ++i){
            if (degree[i] != 2) continue;
            
            // We have found a loop
            int parent = i;
            int curr = i;
            while (!visited[i]){
                HashSet<Integer> currset = adjlist.get(curr);

                // Duct tape: If we removed all the roads, we found a 2 cycle
                // print the reverse and break out of the while loop
                if (currset.isEmpty()){
                    log.write(String.valueOf(parent).getBytes());
                    log.write(' ');
                    log.write(String.valueOf(curr).getBytes());
                    log.write('\n');

                    visited[parent] = true;
                    degree[parent] = 0;
                    break;
                }

                parent = curr;
                curr = currset.toArray(new Integer[2])[0];

                log.write(String.valueOf(curr).getBytes());
                log.write(' ');
                log.write(String.valueOf(parent).getBytes());
                log.write('\n');
                
                visited[curr] = true;
                degree[curr] = 0;

                adjlist.get(parent).remove(curr);
                adjlist.get(curr).remove(parent);
            }
        }
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        Absurdistan3 absurdistan = new Absurdistan3();
        absurdistan.run();
    }
}
