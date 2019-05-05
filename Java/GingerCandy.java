import java.io.*;
import java.util.*;

class Onion{
    private int[] onion;
    private int size;

    public Onion (int size){
        this.onion = new int[size];
        this.size = size;

        for (int i = 0; i < size; ++i){
            this.onion[i] = i;
        }
    }

    // Finds the parent of this node
    int find(int node){
        if (this.onion[node] != node){
            this.onion[node] = find(this.onion[node]);
        }
        return this.onion[node];
    }

    // Returns true if we managed to union the two nodes
    boolean union(int x, int y){
        int parentx = find(x);
        int parenty = find(y);

        if (parentx != parenty){
            this.onion[parentx] = this.onion[parenty];
            return true;
        }
        return false;
    }
}

class Edge implements Comparable<Edge>{
    private int start;
    private int end;
    private int candies;

    public Edge(int start, int end, int candies){
        this.start = start;
        this.end = end;
        this.candies = candies;
    }


    public int getStart(){
        return this.start;
    }

    public int getEnd(){
        return this.end;
    }
    
    public int getCandies(){
        return this.candies;
    }

    public int compareTo(Edge other){
        if (this.getCandies() == other.getCandies()){
            return this.getStart() - other.getStart();
        }
        return this.getCandies() - other.getCandies();
    }
}

public class GingerCandy{
    // Set up the data structures
    PriorityQueue<Edge> heapq = new PriorityQueue<>();
    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int N = Integer.parseInt(dlist[0]);
        int M = Integer.parseInt(dlist[1]);
        int alpha = Integer.parseInt(dlist[2]);

        // Set up the Adjlist
        for (int i = 0; i < N+1; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Set up the onion
        Onion onion = new Onion(N+1);

        for (int i = 0; i < M; ++i){
            dlist = r.readLine().split(" ");
            int u = Integer.parseInt(dlist[0]);
            int v = Integer.parseInt(dlist[1]);
            int c = Integer.parseInt(dlist[2]);
            heapq.add(new Edge(u, v, c));
        }

        // Pull out the edges one by one until we have a cycle
        // Remember to push the edges into the adjlist
        Edge cyclicEdge;
        while (true){
            Edge curr = heapq.poll();

            // If we are out of edges, just print "Poor girl" and give up
            if (curr == null){
                System.out.println("Poor girl");
                return;
            }

            int start = curr.getStart();
            int end = curr.getEnd();
            int candies = curr.getCandies();

            if (onion.union(curr.getStart(), curr.getEnd())){
                adjlist.get(start).add(new Edge(start, end, candies));
                adjlist.get(end).add(new Edge(end, start, candies));
                continue;
            }


            // If we are here, there is a cycle
            cyclicEdge = curr;
            break;
        }

        // Save the number of candies
        int minCandies = cyclicEdge.getCandies();

        // Now we know the minimum number of candies. We just need to find the
        // number of candies in the loop.
        int[] numCandies = new int[N+1];
        boolean[] visited = new boolean[N+1];
        numCandies[cyclicEdge.getEnd()] = 1;
        visited[cyclicEdge.getEnd()] = true;
        Stack<Edge> stack = new Stack<>();
        stack.push(cyclicEdge);

        int endNode = cyclicEdge.getStart();
        
        // So note that we did not push the last edge into the tree
        // We can then traverse from the start to the end
        while (true){
            int curr = stack.pop().getEnd();
            
            // If we have reached the end, stop DFSing
            if (curr == endNode){
                break;
            }

            // Get all the edges to push on the stack
            for (Edge edge : adjlist.get(curr)){
                if (visited[edge.getEnd()]){
                    continue;
                }

                visited[edge.getEnd()] = true;
                numCandies[edge.getEnd()] = numCandies[curr] + 1;
                stack.push(edge);
            }
        }

        // Lastly, print out the number of candies
        long out = minCandies;
        out *= out;
        out += numCandies[endNode] * alpha;
        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{ 
        GingerCandy solution = new GingerCandy();
        solution.run();
    }
}
