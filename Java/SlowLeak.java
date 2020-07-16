import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    private int end;
    private long weight;

    public Edge(int end, long weight){
        this.end = end;
        this.weight = weight;
    }

    public int getEnd(){
        return this.end;
    }

    public long getWeight(){
        return this.weight;
    }

    public int compareTo(Edge other){
        return (this.weight > other.weight)?(1):(-1);
    }
}

public class SlowLeak{
    PriorityQueue<Edge> dijkstra = new PriorityQueue<>();
    long[][] distAPSP; // For APSP
    long[] distDijk; // For Dijkstra

    private void run() throws IOException{ 
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);
        int t = Integer.parseInt(dlist[2]);
        int d = Integer.parseInt(dlist[3]);

        // List of gas filling stations
        int[] stations = new int[t + 1];
        dlist = r.readLine().split(" ");
        for (int i = 0; i < t; ++i){
            stations[i] = Integer.parseInt(dlist[i])-1;
        }
        stations[t] = n-1;
        t++;

        // Initialize distances to infinity
        distAPSP = new long[n][n];
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                distAPSP[i][j] = 1L<<42;
            }
        }

        // Roads
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]) - 1;
            int end = Integer.parseInt(dlist[1]) - 1;
            int weight = Integer.parseInt(dlist[2]);

            distAPSP[start][end] = weight;
            distAPSP[end][start] = weight;
        }

        // Do APSP
        for (int i = 0; i < n; ++i){
            distAPSP[i][i] = 0;
        }

        for (int k = 0; k < n; ++k){
            for (int i = 0; i < n; ++i){
                for (int j = 0; j < n; ++j){
                    distAPSP[i][j] = Math.min(
                            distAPSP[i][j], 
                            distAPSP[i][k] + distAPSP[k][j]
                    );
                }
            }
        }

        for (int i = 0; i < n; ++i){
            distAPSP[i][i] = 1L << 46;
        }

        // Now do Dijkstra
        distDijk = new long[n];
        for (int i = 0; i < n; ++i){
            distDijk[i] = 1L << 44;
        }

        dijkstra.add(new Edge(0, 0));
        long best = 1L << 42;

        while (!dijkstra.isEmpty()){
            Edge curr = dijkstra.poll();
            int end = curr.getEnd();
            long weight = curr.getWeight();

            // Have we reached home?
            if (end == n-1){
                best = Math.min(best, weight);
                continue;
            }

            // Are we journeyed too far?
            if (weight > best) break;
            if (weight > distDijk[end]) continue;

            // If not, look through all the APSP paths, and see where you can go to
            for (int i = 0; i < t; ++i){
                int next = stations[i];
                if (distAPSP[end][next] <= d){
                    long newWeight = distAPSP[end][next] + weight;
                    if (distDijk[next] <= newWeight) continue;
                    distDijk[next] = newWeight;
                    dijkstra.add(new Edge(next, newWeight));
                }
            }
        }

        if (best == (1L << 42)){
            System.out.println("stuck");
        }
        else {
            System.out.println(best);
        }
    }

    public static void main(String[] args) throws IOException{ 
        SlowLeak slowleak = new SlowLeak();
        slowleak.run();
    }
}
