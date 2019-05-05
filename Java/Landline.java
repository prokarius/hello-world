import java.util.*;
import java.io.*;

class Edge implements Comparable<Edge>{
    private int start;
    private int end;
    private long cost;

    public Edge (int start, int end, long cost){
        this.start = start;
        this.end = end;
        this.cost = cost;
    }

    public long getCost(){
        return this.cost;
    }

    public int getStart(){
        return this.start;
    }

    public int getEnd(){
        return this.end;
    }

    public int compareTo(Edge other){
        return (this.cost > other.cost ? 1 : -1);
    }
}

// Since Im going to use Kruskal's lets make an onion class
class Onion {
    private int[] onion;
    private int size;

    public Onion (int size){
        size++;
        this.size = size;
        this.onion = new int[size];

        for (int i = 0; i < size; ++i){
            this.onion[i] = i;
        }
    }

    // Find the parent.
    private int find(int node){
        if (this.onion[node] != node){
            this.onion[node] = find(this.onion[node]);
        }
        return this.onion[node];
    }

    // Returns true if we connected the two components
    public boolean union(int start, int end){
        int parentA = this.find(start);
        int parentB = this.find(end);
        if (parentA != parentB){
            this.onion[parentB] = parentA;
            return true;
        }
        return false;
    }
}

public class Landline{
    // DUCT TAPE LOL
    private void specialCase(BufferedReader r, int numConnections) throws IOException{
        PriorityQueue<Edge> edgeList = new PriorityQueue<>();

        // Check to see if there is an edge between the two buildings.
        // Choose the smallest one
        for (int i = 0; i < numConnections; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            long cost = Long.parseLong(dlist[2]);

            // Check if either start == 1 and end == 2 or start == 2 and end == 1
            if (start + end == 3){
                edgeList.add(new Edge(start, end, cost));
            }
        }

        Edge best = edgeList.poll();

        // If the edgeList is empty, then boohoo.
        if (best == null){
            System.out.println("impossible");
            return;
        }

        // Else print out the cost
        System.out.println(best.getCost());
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // We need a HashSet to store all the insecure buildings
        HashSet<Integer> insecureBuildings = new HashSet<>();

        // Also a pqueue for all the edges
        // And one more for the insecure landlines
        PriorityQueue<Edge> secureConnections = new PriorityQueue<>();
        PriorityQueue<Edge> insecureConnections = new PriorityQueue<>();

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);
        int p = Integer.parseInt(dlist[2]);

        // SPECIAL CASE! If there is only 1 building, it will always work
        if (n == 1){
            System.out.println("0");
            return;
        }

        // Scan in all the insecure buildings
        String[] insecureList = r.readLine().split(" ");
        for (int i = 0; i < p; ++i){
            insecureBuildings.add(Integer.parseInt(insecureList[i]));
        }

        // Oh, if n==p==2, then see if there is a way to connect them
        if (n == 2 && p == 2){
            specialCase(r, m);
            return;
        }

        // Scan in all the edges, pushing them to the relavent queues.
        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            long cost = Long.parseLong(dlist[2]);

            // If the pipeline is between 2 insecure buildings, then ignore it
            // If not, push the edge to the correct queue
            if (insecureBuildings.contains(start) ^ insecureBuildings.contains(end)){
                insecureConnections.add(new Edge(start, end, cost));
            }
            else if (!insecureBuildings.contains(start) && !insecureBuildings.contains(end)){
                secureConnections.add(new Edge(start, end, cost));
            }
        }

        // Since we are going to be running Kruskal's we should create the onion
        Onion onion = new Onion(n);

        long output = 0;

        // Right now we should run Kruskal's on all the secure buildings first
        // Get an MST that consists only of the secure buildings
        int numSecureBuildings = n - p;
        while (numSecureBuildings > 1){
            Edge currEdge = secureConnections.poll();

            // If we ran out of items, just give up
            if (currEdge == null){
                System.out.println("impossible");
                return;
            }

            int start = currEdge.getStart();
            int end = currEdge.getEnd();

            // If we can union these two, add the cost to the total.
            if (onion.union(start, end)){
                output += currEdge.getCost();
                numSecureBuildings--;
            }
        }

        // Now for all the insecure buildings, we try to union them
        int numInsecureBuildings = p;
        while (numInsecureBuildings > 0){

            Edge currEdge = insecureConnections.poll();

            // Same check as above.
            if (currEdge == null){
                System.out.println("impossible");
                return;
            }

            int start = currEdge.getStart();
            int end = currEdge.getEnd();

            // Union it to the MST
            if (onion.union(start, end)){
                output += currEdge.getCost();
                numInsecureBuildings--;
            }
        }

        // If we are here, we have not crashed yet! Yay
        // It means we have an answer, go print it out :)
        System.out.println(output);
    }

    public static void main(String[] args) throws IOException{
        Landline landline = new Landline();
        landline.run();
    }
}
