import java.io.*;
import java.util.*;

class Pair{
    int node;
    boolean colour;

    public Pair(int node, boolean colour){
        this.node = node;
        this.colour = colour;
    }
}

public class Amanda{
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    boolean[] visited;
    boolean[] lounge;

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        visited = new boolean[n+1];
        lounge = new boolean[n+1];

        // Create the adjlist (such a bad idea of 200k arraylists...)
        for (int i = 0; i <= n; ++i){
            adjlist.add(new ArrayList<>());
        }

        int out = 0;

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            int numLounge = Integer.parseInt(dlist[2]);

            // If the number of lounges is 2 or 0, we can process it immediately
            if (numLounge == 0){
                // Check both sides to see if we have visited them before
                if (visited[start] && lounge[start]){
                    System.out.println("impossible");
                    return;
                }
                if (visited[end] && lounge[end]){
                    System.out.println("impossible");
                }

                // Set both sides to have no lounges
                visited[start] = true;
                visited[end] = true;
                lounge[start] = false;
                lounge[end] = false;
            }
            // Same idea for if there are 2 lounges already
            else if (numLounge == 2){
                if (visited[start] && !lounge[start]){
                    System.out.println("impossible");
                    return;
                }
                if (visited[end] && !lounge[end]){
                    System.out.println("impossible");
                }

                // Set both sides to have no lounges
                if (!visited[start]) out++;
                if (!visited[end]) out++;
                visited[start] = true;
                visited[end] = true;
                lounge[start] = true;
                lounge[end] = true;
            }

            // Else, we have 1 lounge. Add that edge to the adjList
            else {
                adjlist.get(start).add(end);
                adjlist.get(end).add(start);
            }
        }

        // Duct tape: Go through each edge to make sure we did not visit both vertices before
        for (int i = 0; i <= n; ++i){
            for (int neighbour : adjlist.get(i)){
                if (visited[i] & visited[neighbour]){
                    if (!lounge[i] ^ lounge[neighbour]){
                        System.out.println("impossible");
                        return;
                    }
                }
            }
        }

        // Right, now it's time to do 0-1 colouring on all the components
        ArrayList<Integer> nodes;
        LinkedList<Pair> dfs = new LinkedList<>();
        for (int i = 1; i <= n; ++i){
            if (visited[i]) continue;

            // Else do dfs
            // Sorry, I'm a bit lazy to think of a better way than to do dfs twice
            int errors = 0;
            int best = 1<<29;
            int numTrue = 0;
            nodes = new ArrayList<>();
            dfs.addFirst(new Pair(i, false));
            visited[i] = true;
            lounge[i] = false;

            while (!dfs.isEmpty()){
                Pair current = dfs.pollFirst();
                int curr = current.node;
                nodes.add(curr);
                boolean colour = current.colour;

                if (colour) numTrue++;

                for (int neighbour : adjlist.get(curr)){
                    // If we have visited this neighbour before, see if the colour
                    // matches the flip side of it
                    if (visited[neighbour]){
                        if (lounge[neighbour] == colour){
                            // Break out of everything by resetting the dfs list
                            errors++;
                            numTrue = 1<<29;
                            dfs.clear();
                            break;
                        }
                        continue;
                    }

                    // Else, we continue to colour
                    visited[neighbour] = true;
                    lounge[neighbour] = !colour;
                    nodes.add(neighbour);

                    // Also, add to the dfs queue
                    dfs.addFirst(new Pair(neighbour, !colour));
                }
            }

            // Update the best
            best = Math.min(best, numTrue);

            // Reset the visited array and do it again
            for (int node : nodes){
                visited[node] = false;
            }

            numTrue = 0;
            dfs.addFirst(new Pair(i, true));
            visited[i] = true;
            lounge[i] = true;

            while (!dfs.isEmpty()){
                Pair current = dfs.pollFirst();
                int curr = current.node;
                boolean colour = current.colour;

                if (colour) numTrue++;

                for (int neighbour : adjlist.get(curr)){
                    // If we have visited this neighbour before, see if the colour
                    // matches the flip side of it
                    if (visited[neighbour]){
                        if (lounge[neighbour] == colour){
                            // Break out of everything by resetting the dfs list
                            errors++;
                            numTrue = 1<<29;
                            dfs.clear();
                            break;
                        }
                        continue;
                    }

                    // Else, we continue to colour
                    visited[neighbour] = true;
                    lounge[neighbour] = !colour;
                    nodes.add(neighbour);

                    // Also, add to the dfs queue
                    dfs.addFirst(new Pair(neighbour, !colour));
                }
            }

            // Update the best
            best = Math.min(best, numTrue);

            // Right, how many errors do we have?
            if (errors == 2){
                System.out.println("impossible");
                return;
            }

            // Else add the number of trues to the output;
            out += best;

            // Also turn on all the nodes that we have visited before
            for(int node : nodes){
                visited[node] = true;
            }
        }

        // Now just print out!
        System.out.println(out);

    }

    public static void main(String[] args) throws IOException{
        Amanda amanda = new Amanda();
        amanda.run();
    }
}

