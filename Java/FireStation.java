import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    int end;
    int dist;

    public Edge(int end, int dist){
        this.end = end;
        this.dist = dist;
    }

    public int compareTo(Edge other){
        return (this.dist > other.dist) ? 1 : -1;
    }
}

public class FireStation{
    boolean[] stations;
    int[] distance;
    ArrayList<Integer> listStations = new ArrayList<>();
    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();

    private void doDijkstra(int node, int n){
        // Set up the data structures
        PriorityQueue<Edge> dijkstra = new PriorityQueue<>();
        distance = new int[n];
        for (int i = 0; i < n; ++i){
            distance[i] = 1<<30;
        }

        // Populate the PQueue
        dijkstra.add(new Edge(node, 0));
        distance[node] = 0;
        for (int station : listStations){
            distance[station] = 0;
            dijkstra.add(new Edge(station, 0));
        }

        // Do dijkstra
        while (!dijkstra.isEmpty()){
            Edge curr = dijkstra.poll();
            int start = curr.end;
            int currDist = curr.dist;

            if (distance[start] < currDist) continue;
            
            for (Edge neighborEdge : adjlist.get(start)){
                int end = neighborEdge.end;
                int newDist = currDist + neighborEdge.dist;

                if (distance[end] <= newDist) continue;
                distance[end] = newDist;
                dijkstra.add(new Edge(end, newDist));
            }
        }
    }

    private void run(BufferedReader r) throws IOException{
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int f = Integer.parseInt(dlist[0]);
        int n = Integer.parseInt(dlist[1]);

        // Initialise data structures
        stations = new boolean[n];
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        for (int i = 0; i < f; ++i){
            int station = Integer.parseInt(r.readLine()) - 1;
            stations[station] = true;
            listStations.add(station);
        }

        // God the input parsing is such a pain
        String str = r.readLine();
        while (str != null && !str.equals("")){
            dlist = str.split(" ");
            int start = Integer.parseInt(dlist[0]) - 1;
            int end = Integer.parseInt(dlist[1]) - 1;
            int dist = Integer.parseInt(dlist[2]);

            adjlist.get(start).add(new Edge(end, dist));
            adjlist.get(end).add(new Edge(start, dist));
            str = r.readLine();
        }

        int best = 0;
        int bestDist = 1<<30;

        // Simulate dijkstra for all remaining intersections.
        for (int i = 0; i < n; ++i){
            if (stations[i]) continue;
            doDijkstra(i, n);

            // Find the furthest point in each test case
            int currBest = -1;
            for (int j = 0; j < n; ++j){
                currBest = Math.max(distance[j], currBest);
            }

            // Is it nearer than what we have now?
            if (currBest < bestDist){
                bestDist = currBest;
                best = i;
            }
        }

        // Print the output, don't forget to add one back.
        // Stupid 1 based indexing...
        System.out.println(best + 1);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());
        r.readLine();  // Some weird input formatting going on...

        for (int i = 0; i < testcases; ++i){
            FireStation firestation = new FireStation();
            firestation.run(r);
        }
    }
}

