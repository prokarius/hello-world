import java.util.*;
import java.io.*;

// Edge class to abstract out the adj list
class Edge implements Comparable<Edge>{
    private int end;
    private long weight;

    public Edge (int end, long weight){
        this.end = end;
        this.weight = weight;
    }

    // Getters and Setters
    public int getEnd(){
        return this.end;
    }

    public long getWeight(){
        return this.weight;
    }

    // Compare by weight, then start, then end
    public int compareTo(Edge other){
        if (this.weight == other.weight) {
            return this.end - other.end;
        }
        return (this.weight > other.weight) ? 1 : -1;
    }
}

public class Bumped{
    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();
    ArrayList<Edge> flights = new ArrayList<>();
    long[] costFromStart;
    long[] costFromEnd;

    // Do Dijkstra
    private void dijkstra (int startNode, long[] cost, int n){
        boolean[] visited = new boolean[n];
        PriorityQueue<Edge> heapq = new PriorityQueue<>();
        cost[startNode] = 0;
        heapq.add(new Edge(startNode, 0));
        while (!heapq.isEmpty()){
            Edge top = heapq.poll();
            int node = top.getEnd();
            long currWeight = top.getWeight();
            if (visited[node]) continue;
            if (cost[node] < currWeight) continue;
            visited[node] = true;
            for (Edge i : adjlist.get(node)){
                int nextNode = i.getEnd();
                long nextWeight = currWeight + i.getWeight();
                if (cost[nextNode] > nextWeight){
                    cost[nextNode] = nextWeight;
                    heapq.add(new Edge(nextNode, currWeight + i.getWeight()));
                }
            }
        }
    }

    public void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);
        int f = Integer.parseInt(dlist[2]);
        int travelStart = Integer.parseInt(dlist[3]);
        int travelEnd = Integer.parseInt(dlist[4]);

        // Initialise cost array
        costFromStart = new long[n];
        costFromEnd = new long[n];
        for (int i = 0; i < n; ++i){
            costFromStart[i] = 1L<<50;
            costFromEnd[i] = 1L<<50;
        }
        costFromStart[travelStart] = 0;
        costFromEnd[travelEnd] = 0;

        // Initialise arrayLists
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Scan in roads
        for (int i = 0; i < m; ++i){
            String[] ph = r.readLine().split(" ");
            int start = Integer.parseInt(ph[0]);
            int end = Integer.parseInt(ph[1]);
            int weight = Integer.parseInt(ph[2]);
            adjlist.get(start).add(new Edge(end, weight));
            adjlist.get(end).add(new Edge(start, weight));
        }

        // Scan in flights
        for (int i = 0; i < f; ++i){
            String[] ph = r.readLine().split(" ");
            int start = Integer.parseInt(ph[0]);
            int end = Integer.parseInt(ph[1]);
            flights.add(new Edge(start, end));
        }

        // Do Dijkstra from 2 directions
        dijkstra(travelStart, costFromStart, n);
        dijkstra(travelEnd, costFromEnd, n);

        // For each flight, find the cheapest cost to travel from a city to the
        // departure city, and from the city of arrival to final destination.
        // Add the cost up and see if it's better than what we have so far.
        long best = 1L << 62;
        for (Edge i : flights){
            int start = i.getEnd();
            long end = i.getWeight();

            long curr = costFromStart[i.getEnd()] + costFromEnd[(int) i.getWeight()];
            if (best > curr) best = curr;
        }

        // Wait, can we actually just drive from start to end?
        if (costFromStart[travelEnd] < best) best = costFromStart[travelEnd];

        // Print that shit.
        System.out.println(best);
    }

    public static void main(String[] args) throws IOException{
        Bumped bumped = new Bumped();
        bumped.run();
    }
}
