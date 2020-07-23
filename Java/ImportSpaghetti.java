import java.io.*;
import java.util.*;

class Edge {
    int node;
    int distance;

    public Edge(int node, int distance){
        this.node = node;
        this.distance = distance;
    }
}

public class ImportSpaghetti{
    HashMap<String, Integer> mapping = new HashMap<>();
    HashMap<Integer, String> revMapping = new HashMap<>();
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();

    private int bfs(int start, int n){
        int[] visited = new int[n+1]; 

        Queue<Edge> queue = new LinkedList<>();

        // Duct tape
        for (int neighbour : adjlist.get(start)){
            queue.add(new Edge(neighbour, 1));
        }

        while (!queue.isEmpty()){
            Edge curr = queue.poll();
            int node = curr.node;
            int distance = curr.distance;

            // Are we at the start again...?
            if (node == start){
                return distance;
            }

            // If we reached a node before, forget it
            if (visited[node] != 0){
                continue;
            }

            // If not, set the distance, and visit all the neighbors
            visited[node] = distance;

            for (int neighbour : adjlist.get(node)){
                queue.add(new Edge(neighbour, distance + 1));
            }
        }

        // Oh we are at the end... Bummer
        return 1<<30;
    }

    private void printShortest(int start, int n){
        int[] prev = new int[n+1];

        Queue<Edge> queue = new LinkedList<>();

        for (int neighbour : adjlist.get(start)){
            queue.add(new Edge(neighbour, start));
        }

        while (!queue.isEmpty()){
            Edge curr = queue.poll();
            int node = curr.node;
            int back = curr.distance;

            if (node == start){
                prev[node] = back;
                break;
            }

            if (prev[node] != 0) continue;
            prev[node] = back;

            // Visit all the neighbors
            for (int neighbour : adjlist.get(node)){
                queue.add(new Edge(neighbour, node));
            }
        }

        // OK yay we have the the cycle, time to print it out
        LinkedList<Integer> cycle = new LinkedList<>();
        cycle.addFirst(start);
        int node = prev[start];
        while (node != start){
            cycle.addFirst(node);
            node = prev[node];
        }

        // Print that shit
        for (int out : cycle){
            System.out.printf("%s ", revMapping.get(out));
        }
        System.out.println("");
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        adjlist.add(new ArrayList<>());

        String[] dlist = r.readLine().split(" ");
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
            mapping.put(dlist[i], i+1);
            revMapping.put(i+1, dlist[i]);
        }

        // Scan in the sections. They are given in order
        for (int i = 1; i <= n; ++i){
            dlist = r.readLine().split(" ");
            int k = Integer.parseInt(dlist[1]);
    
            // Whoever created this is sick...
            for (int a = 0; a < k; ++a){
                dlist = r.readLine().split(",? "); // Regex matching... hope it's fast enough

                for (int j = 1; j < dlist.length; ++j){
                    int neighbor = mapping.get(dlist[j]);
                    adjlist.get(i).add(neighbor);
                }
            }
        }

        // adjlist now contains our adjlist
        // Do BFS and cycle detection for each node I guess...?
        // O(VE) apparently passes in Kotlin... :\
        int best = 1<<20;
        int bestLoop = -1;
        for (int start = 1; start <= n; ++start){
            int shortestLoop = bfs(start, n);
            if (shortestLoop < best){
                best = shortestLoop;
                bestLoop = start;
            }
        }

        // Right, so we just need to print it out I guess...?
        if (best == 1<<20){
            System.out.println("SHIP IT");
        }
        else {
            printShortest(bestLoop, n);
        }
    }

    public static void main(String[] args) throws IOException{
        ImportSpaghetti spaghetti = new ImportSpaghetti();
        spaghetti.run();
    }
}

