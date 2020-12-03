import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    int end;
    long dist;

    public Edge(int end, long distance){
        this.end = end;
        this.dist = distance;
    }

    public int compareTo(Edge other){
        if (this.dist > other.dist) return 1;
        return (this.end > other.end ? 1 : -1);
    }
}

public class ForestFruits{

    ArrayList<ArrayList<Edge>> adjList = new ArrayList<>();
    PriorityQueue<Edge> dijkstra = new PriorityQueue<>();
    long distance[];
    ArrayList<Long> fruits = new ArrayList<>();

    private void doDijkstra(){
        dijkstra.add(new Edge(0, 0));
        distance[0] = 0;

        while(!dijkstra.isEmpty()){
            Edge curr = dijkstra.poll();
            int start = curr.end;
            long dist = curr.dist;

            if (distance[start] < dist) continue;

            // Visit all the neighbors
            for (Edge edge : adjList.get(start)){
                int neighbor = edge.end;
                long newDist = edge.dist + dist;

                if (distance[neighbor] <= newDist) continue;
                distance[neighbor] = newDist;
                dijkstra.add(new Edge(neighbor, newDist));
            }
        }
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int v = Integer.parseInt(dlist[0]);
        int e = Integer.parseInt(dlist[1]);
        int c = Integer.parseInt(dlist[2]);
        int k = Integer.parseInt(dlist[3]);
        int m = Integer.parseInt(dlist[4]);

        // Initialize my data structures
        distance = new long[v];
        for (int i = 0; i < v; ++i){
            adjList.add(new ArrayList<>());
            distance[i] = 1L << 56;
        }

        for (int i = 0; i < e; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]) - 1;
            int end = Integer.parseInt(dlist[1]) - 1;
            long dist = Integer.parseInt(dlist[2]);

            adjList.get(start).add(new Edge(end, dist));
            adjList.get(end).add(new Edge(start, dist));
        }

        // Do dijkstra
        doDijkstra();

        // Then scan in all the clearings
        dlist = r.readLine().split(" ");
        for (int i = 0; i < c; ++i){
            int fruit = Integer.parseInt(dlist[i]) - 1;
            fruits.add(distance[fruit]);
        }

        // Sort them, and see how far
        Collections.sort(fruits);

        // If M > K, keep K. If K > M, keep M
        // Break if we have too many days to get fruits
        int day = Math.min(k, m);
        if (day > c){
            System.out.println("-1");
            return;
        }

        long longestDist = fruits.get(day - 1);
        if (longestDist == 1L<<56){
            System.out.println("-1");
            return;
        }

        System.out.println(longestDist * 2);
    }

    public static void main(String[] args) throws IOException{
        ForestFruits forestFruits = new ForestFruits();
        forestFruits.run();
    }
}

