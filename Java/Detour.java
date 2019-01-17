import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    private int end;
    private long distance;

    public Edge (int end, long distance){
        this.end = end;
        this.distance = distance;
    }

    public long getDistance(){
        return this.distance;
    }

    public int getEnd(){
        return this.end;
    }

    public int compareTo (Edge other){
        if (other.distance == this.distance){
            return this.end - other.end;
        }
        return (this.distance > other.distance ? 1 : -1);
    }
}

public class Detour{
    private final long INF = 1L << 56;

    private int[] comesFrom;
    private long[] distance;
    private PriorityQueue<Edge> dijkstra = new PriorityQueue<>();
    private ArrayList<HashMap<Integer, Edge>> adjList = new ArrayList<>();

    public void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Initialise the adjList
        for (int i = 0; i < n; ++i){
            adjList.add(new HashMap<>());
        }

        // Scan in the roads
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            int dist = Integer.parseInt(dlist[2]);

            adjList.get(start).put(end, new Edge(end, dist));
            adjList.get(end).put(start, new Edge(start, dist));
        }

        // Initialise the distance array and the comesFrom array
        comesFrom = new int[n];
        distance = new long[n];
        for (int i = 2; i < n; ++i){
            distance[i] = INF;
        }
        distance[0] = INF;

        // Do dijkstra
        dijkstra.add(new Edge(1, 0));

        while (!dijkstra.isEmpty()){
            Edge edge = dijkstra.poll();
            int curr = edge.getEnd();
            long dist = edge.getDistance();

            if (distance[curr] < dist) continue;

            for (Edge neighbouringEdge : adjList.get(curr).values()){
                int neighbour = neighbouringEdge.getEnd();
                if (distance[neighbour] <= dist + neighbouringEdge.getDistance()) continue;

                distance[neighbour] = dist + neighbouringEdge.getDistance();
                comesFrom[neighbour] = curr;

                dijkstra.add(new Edge(neighbour, distance[neighbour]));
            }
        }

        // OK we now have the fastest route from Amsterdam to everywhere.
        // Delete the edges. BUT NOT THE BIDIRECTIONAL EDGE
        // Only the edge that brings you closer to Amsterdam
        for (int i = 2; i < n; ++i){
            adjList.get(i).remove(comesFrom[i]);
        }
        adjList.get(0).remove(comesFrom[0]);

        // Reset our data structures
        for (int i = 0; i < n; ++i){
            comesFrom[i] = 0;
            distance[i] = 0;
        }

        // Lastly, run BFS or something
        Queue<Integer> bfsQueue = new LinkedList<>();
        bfsQueue.add(0);
        comesFrom[0] = -1;
        distance[0] = 1;

        while (!bfsQueue.isEmpty()){
            int curr = bfsQueue.poll();
            if (curr == 1) break;

            for (int neighbour : adjList.get(curr).keySet()){
                if (distance[neighbour] == 1) continue;
                comesFrom[neighbour] = curr;
                distance[neighbour] = 1;
                bfsQueue.add(neighbour);
            }
        }

        // If we fail to reach the end, print impossible;
        if (distance[1] == 0){
            System.out.println("impossible");
            return;
        }

        // Print that shit
        OutputStream log = new BufferedOutputStream (System.out);
        LinkedList<Integer> output = new LinkedList<>();

        int curr = 1;
        while (curr != -1){
            output.addFirst(curr);
            curr = comesFrom[curr];
        }

        log.write(String.valueOf(output.size()).getBytes());
        log.write(' ');

        for (int node : output){
            log.write(String.valueOf(node).getBytes());
            log.write(' ');
        }

        log.write('\n');
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        Detour detour = new Detour();
        detour.run();
    }
}
