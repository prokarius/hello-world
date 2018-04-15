import java.io.*;
import java.util.*;

// Encapsulates an edge.
// Start point doesn't need to be stored.
class Edge implements Comparable<Edge>{
    private int end;
    private int weight;

    public Edge(int end, int weight){
        this.end = end;
        this.weight = weight;
    }

    public int getEnd(){
        return this.end;
    }

    public int getWeight(){
        return this.weight;
    }

    public int compareTo(Edge other){
        return this.weight - other.weight;
    }
}

public class WalkForest{
    public static void main(String[] args) throws IOException{
        // Scan in input
        // Don't forget to pass the scanner around
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] nandm = r.readLine().split(" ");
        int n = Integer.parseInt(nandm[0]);
        while (n != 0){
            int M = Integer.parseInt(nandm[1]);
            run(n, M, r);
            nandm = r.readLine().split(" ");
            n = Integer.parseInt(nandm[0]);
        }
    }

    private static void run(int n, int M, BufferedReader r) throws IOException{
        PriorityQueue<Edge> pqueue = new PriorityQueue<>();
        ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();
        int[] distance = new int[n];
        int[] count = new int[n];

        // Initialise the stuff
        for (int i=0; i<n; ++i){
            adjlist.add(new ArrayList<>());
            distance[i] = 2000000000;
            count[i] = -1;
        }

        // Populate the adjacency list
        for (int i=0; i<M; ++i){
            String[] input = r.readLine().split(" ");
            int start = Integer.parseInt(input[0]) - 1;
            int end = Integer.parseInt(input[1]) - 1;
            int weight = Integer.parseInt(input[2]);
            adjlist.get(start).add(new Edge(end, weight));
            adjlist.get(end).add(new Edge(start, weight));
        }

        // Set the distance to 0 for the end node and Dijkstra backwards
        distance[1] = 0;
        pqueue.add(new Edge(1,0));

        // From the end node, find the shortest distance to all other nodes.
        while (!pqueue.isEmpty()){
            Edge curr = pqueue.poll();
            if (curr.getWeight() > distance[curr.getEnd()]){
                continue;
            }

            for (Edge edge : adjlist.get(curr.getEnd())){
                int neighbour = edge.getEnd();
                if (distance[neighbour] > edge.getWeight() + curr.getWeight()){
                    distance[neighbour] = edge.getWeight() + curr.getWeight();
                    pqueue.add(new Edge(neighbour, distance[neighbour]));
                }
            }
        }

        // Toposort this list and print out the solution
        System.out.println(pathCount(1, count, adjlist, distance));
    }

    // Does a DP backwards from count
    // Essentially simulating a toposort, and a count sequence.
    // Returns the number of paths from vertex 0 to vertex vertex.
    private static int pathCount(int vertex, int[] counter, ArrayList<ArrayList<Edge>> adjlist, int[] distance){
        // If we have been here before, return the cache
        if (counter[vertex] >= 0){
            return counter[vertex];
        }

        // If we are at the starting point, return 1 way
        if (vertex == 0){
            return 1;
        }

        int currcount = 0;

        // Else for each new vertex we can reach.
        for (Edge edge : adjlist.get(vertex)){
            // If the distance to that vertex is more than the current distance.
            // Add the number of ways to reach there into the a counter.
            // Then return that counter.
            if (distance[vertex] < distance[edge.getEnd()]){
                currcount += pathCount(edge.getEnd(), counter, adjlist, distance);
            }
        }
        counter[vertex] = currcount;
        return currcount;
    }
}
