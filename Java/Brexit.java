import java.util.*;
import java.io.*;

public class Brexit{
    private ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();
    private LinkedList<Integer> queue = new LinkedList<>();

    private void run() throws IOException{
        // Read in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int C = Integer.parseInt(dlist[0]);
        int P = Integer.parseInt(dlist[1]);
        int X = Integer.parseInt(dlist[2]);
        int L = Integer.parseInt(dlist[3]);

        // Initialise our adjlist etc.
        for (int i = 0; i <= C; ++i){
            adjList.add(new ArrayList<>());
        }

        // Scan in the connections
        for (int i = 0; i < P; ++i){
            String[] ph = r.readLine().split(" ");
            int start = Integer.parseInt(ph[0]);
            int end = Integer.parseInt(ph[1]);
            adjList.get(start).add(end);
            adjList.get(end).add(start);
        }

        // We save the number of countries that are leaving in an array
        // This is so that we have an easy reference.
        boolean[] visited = new boolean[C+1];
        int[] numout = new int[C+1];
        int[] connect = new int[C+1];
        for (int i = 0; i <= C; ++i){
            numout[i] = adjList.get(i).size();
            connect[i] = adjList.get(i).size();
        }

        // Now we create a LinkedList of who is going to leave
        // And mark them as left
        queue.addFirst(L);
        visited[L] = true;

        // While the queue is not empty, we get make the country leave
        while (queue.size() > 0){
            int leave = queue.pollLast();

            // If our country is leaving, just print leave and quit
            if (leave == X){
                System.out.println("leave");
                return;
            }

            // For each of the connections to the country that left, we reduce
            // the number of outgoing nodes by 1
            for (int next : adjList.get(leave)){
                numout[next] -= 1;

                // If the number of outgoing connections is now half of what it can
                // be, we make the country leave by pushing it into the queue.
                // But only if it hasn't already left.
                // Remember to add it as left.
                if (numout[next] * 2 <= connect[next] && !visited[next]){
                    visited[next] = true;
                    queue.addFirst(next);
                }
            }
        }

        System.out.println("stay");
    }

    public static void main(String[] args) throws IOException{
        Brexit brexit = new Brexit();
        brexit.run();
    }
}
