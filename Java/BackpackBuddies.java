import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    int end;
    int distance;

    public Edge(int end, int distance){
        this.end = end;
        this.distance = distance;
    }

    public int compareTo(Edge other){
        return this.distance - other.distance;
    }
}

public class BackpackBuddies{
    ArrayList<HashMap<Integer, Integer>> adjlist = new ArrayList<>();
    PriorityQueue<Edge> dijkstra = new PriorityQueue<>();
    int[] distanceNight;
    int[] distanceDay;

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Create and populate the adjlist
        for (int i = 0; i < n; ++i){
            adjlist.add(new HashMap<>());
        }

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int u = Integer.parseInt(dlist[0]);
            int v = Integer.parseInt(dlist[1]);
            int d = Integer.parseInt(dlist[2]);

            // Short circuit if the path is stupid
            if (u == v) continue;

            if (!adjlist.get(u).containsKey(v) || adjlist.get(u).get(v) > d){
                adjlist.get(u).put(v, d);
            }
            if (!adjlist.get(v).containsKey(u) || adjlist.get(v).get(u) > d){
                adjlist.get(v).put(u, d);
            }
        }

        // Do dijkstra to find when night will reach the end
        distanceNight = new int[n];
        distanceDay = new int[n];
        for (int i = 0; i < n; ++i){
            distanceNight[i] = 1 << 25;
            distanceDay[i] = 1 << 25;
        }

        dijkstra.add(new Edge(0, 0));
        while (!dijkstra.isEmpty()){
            Edge curr = dijkstra.poll();
            int end = curr.end;
            int dist = curr.distance;

            // Have we reached the end, or have we already arrived?
            if (end == n-1) break;
            if (distanceNight[end] < dist) continue;

            // Go to the rest of the edges
            for (Map.Entry<Integer, Integer> next : adjlist.get(end).entrySet()){
                int neighbour = next.getKey();
                int newDist = next.getValue();
                if (distanceNight[neighbour] <= dist + newDist) continue;
                distanceNight[neighbour] = dist + newDist;
                dijkstra.add(new Edge(neighbour, dist + newDist));
            }
        }

        // After dijkstra, distance[n-1] is how far Knight has travelled.
        int distanceKnight = distanceNight[n-1]-1;

        // To get how far Day travels, we need to change the distance computation...
        dijkstra.clear();

        // This is for Mr Day
        dijkstra.add(new Edge(0, 0));
        while (!dijkstra.isEmpty()){
            Edge curr = dijkstra.poll();
            int end = curr.end;
            int dist = curr.distance;

            // Have we reached the end, or have we already arrived?
            if (end == n-1) break;
            if (distanceDay[end] < dist) continue;

            // Go to the rest of the edges
            for (Map.Entry<Integer, Integer> next : adjlist.get(end).entrySet()){
                int neighbour = next.getKey();
                int newDist = next.getValue();

                // Here, if we are alredy 12 hours into the day, we rest for the night
                if (dist % 12 + newDist > 12){
                    newDist += (12 - (dist % 12));
                }

                if (distanceDay[neighbour] <= dist + newDist) continue;
                distanceDay[neighbour] = dist + newDist;
                dijkstra.add(new Edge(neighbour, dist + newDist));
            }
        }

        // After dijkstra, distance[n-1] is how far Day has travelled.
        int distanceMrDay = distanceDay[n-1]-1;

        // So the amount of time = number of 12 hours * 24 hours + leftover time
        distanceKnight = ((distanceKnight) / 12) * 24 + (distanceKnight % 12);
        distanceMrDay = ((distanceMrDay) / 12) * 24 + (distanceMrDay % 12);

        System.out.println(distanceMrDay - distanceKnight);
    }

    public static void main(String[] args) throws IOException{
        BackpackBuddies backpack = new BackpackBuddies();
        backpack.run();
    }
}

