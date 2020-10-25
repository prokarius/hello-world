import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    int end;
    int weight;

    public Edge (int end, int weight){
        this.end = end;
        this.weight = weight;
    }

    public int compareTo (Edge other){
        return (this.weight > other.weight ? 1 : -1);
    }
}

public class DestinationUnknown{
    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();
    ArrayList<Integer> possible = new ArrayList<>();

    int[] distS, distG, distH;
    int edge;

    private void doDijkstra(int s, int[] dist){
        PriorityQueue<Edge> dijkstra = new PriorityQueue<>();

        dijkstra.add(new Edge(s, 0));
        dist[s] = 0;

        while (!dijkstra.isEmpty()){
            Edge curr = dijkstra.poll();
            int start = curr.end;
            int cost = curr.weight;

            if (dist[start] < cost) continue;
            dist[start] = cost;

            for (Edge edge : adjlist.get(start)){
                int newCost = cost + edge.weight;
                int end = edge.end;

                if (dist[end] <= newCost) continue;
                dist[end] = newCost;
                dijkstra.add(new Edge(end, newCost));
            }
        }
    }

    private void run(BufferedReader r, OutputStream log) throws IOException{
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);
        int t = Integer.parseInt(dlist[2]);

        for (int i = 0; i < n+1; ++i){
            adjlist.add(new ArrayList<>());
        }

        dlist = r.readLine().split(" ");
        int s = Integer.parseInt(dlist[0]);
        int g = Integer.parseInt(dlist[1]);
        int h = Integer.parseInt(dlist[2]);

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            int length = Integer.parseInt(dlist[2]);
            adjlist.get(start).add(new Edge(end, length));
            adjlist.get(end).add(new Edge(start, length));

            if ((start == g && end == h) || (start == h && end == g)){
                edge = length;
            }
        }

        for (int i = 0; i < t; ++i){
            possible.add(Integer.parseInt(r.readLine()));
        }

        // Do Dijkstra from start, g and h
        distS = new int[n+1];
        distG = new int[n+1];
        distH = new int[n+1];

        for (int i = 0; i <= n; ++i){
            distS[i] = 1<<30;
            distG[i] = 1<<30;
            distH[i] = 1<<30;
        }

        doDijkstra(s, distS);
        doDijkstra(g, distG);
        doDijkstra(h, distH);

        // Now see if the distance for all the possible destinations can
        // pass through G or H in either directions
        ArrayList<Integer> out = new ArrayList<>();
        for (int i : possible){
            if (distS[i] == distS[g] + distH[i] + edge ||
                distS[i] == distS[h] + distG[i] + edge){
                out.add(i);
                }
        }

        Collections.sort(out);

        for (int i : out){
            System.out.printf("%d ", i);
        }
        System.out.println("");
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        int testcases = Integer.parseInt(r.readLine());
        for (int i = 0; i < testcases; ++i){
            DestinationUnknown unknown = new DestinationUnknown();
            unknown.run(r, log);
        }
    }
}

