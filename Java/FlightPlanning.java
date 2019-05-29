import java.io.*;
import java.util.*;

class Pair{
    private int x;
    private int y;

    public Pair(int x, int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return this.x;
    }

    public int getY(){
        return this.y;
    }
}

class Edge{
    private int start;
    private int end;

    public Edge(int start, int end){
        this.start = start;
        this.end = end;
    }

    public int getStart(){
        return this.start;
    }

    public int getEnd(){
        return this.end;
    }

    public boolean equals(Edge other){
        if (this.end == other.end){
            return this.start == other.start;
        }
        else if (this.start == other.end){
            return this.end == other.start;
        }
        return false;
    }
}

public class FlightPlanning{
    int n;

    // Save the list of edges
    ArrayList<Edge> edgelist = new ArrayList<>();
    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();

    // This edge is the blacklisted one
    Edge blacklistedEdge;

    // This is the visitedArray
    boolean[] visited = new boolean[n+1];

    // Run BFS here
    // I know there is code repetition here. STFU.
    private int getFurthest(int node){
        LinkedList<Pair> queue = new LinkedList<>();
        Pair furthest = new Pair(node, 0);
        queue.addFirst(furthest);

        visited[node] = true;

        while(!queue.isEmpty()){
            furthest = queue.pollLast();

            for (Edge edge : adjlist.get(furthest.getX())){
                if (edge.equals(blacklistedEdge)) continue;
                int neighbour = edge.getEnd();

                if (visited[neighbour]) continue;

                visited[neighbour] = true;
                queue.addFirst(new Pair(neighbour, furthest.getY() + 1));
            }
        }

        return furthest.getX();
    }

    // Yes, more code repetition, STFU.
    private int getMidpoint(int node, int distance){
        LinkedList<Pair> queue = new LinkedList<>();
        Pair furthest = new Pair(node, 0);
        queue.addFirst(furthest);

        boolean[] visited = new boolean[n+1];
        int[] parent = new int[n+1];
        visited[node] = true;

        while(!queue.isEmpty()){
            furthest = queue.pollLast();

            for (Edge edge : adjlist.get(furthest.getX())){
                if (edge.equals(blacklistedEdge)) continue;
                int neighbour = edge.getEnd();

                if (visited[neighbour]) continue;

                visited[neighbour] = true;
                parent[neighbour] = furthest.getX();
                queue.addFirst(new Pair(neighbour, furthest.getY() + 1));
            }
        }

        ArrayList<Integer> path = new ArrayList<>();

        // Now we are going to find the path from furthest to the end
        int endNode = furthest.getX();

        while (endNode != node){
            path.add(endNode);
            endNode = parent[endNode];
        }

        path.add(node);

        return path.get(distance);
    }

    // Precondition: node is an edge node
    // Finds the diameter of a given tree
    private int getDiameter(int node){
        LinkedList<Pair> queue = new LinkedList<>();
        Pair furthest = new Pair(node, 0);
        queue.addFirst(furthest);

        visited = new boolean[n+1];
        visited[node] = true;

        while(!queue.isEmpty()){
            furthest = queue.pollLast();

            for (Edge edge : adjlist.get(furthest.getX())){
                if (edge.equals(blacklistedEdge)) continue;
                int neighbour = edge.getEnd();

                if (visited[neighbour]) continue;

                visited[neighbour] = true;
                queue.addFirst(new Pair(neighbour, furthest.getY() + 1));
            }
        }

        return furthest.getY();
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        n = Integer.parseInt(r.readLine());

        // Initialise the adjlist
        for (int i = 0; i <= n; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Push the edges into the adjlist
        for (int i = 1; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            Edge edge = new Edge(start, end);
            Edge revEdge = new Edge(end, start);

            adjlist.get(start).add(edge);
            adjlist.get(end).add(revEdge);

            edgelist.add(edge);
        }

        int best = 9999;
        Edge removedEdge = new Edge(0,0);
        Edge inputEdge = new Edge(0,0);

        // For each of the current edges, remove it and find the distance of the two
        // trees that is formed.
        // The diameter of the new tree that's formed is the sum of radius of the
        // 2 trees + 1 (for the new edge)
        for (Edge curr : edgelist){
            // Initialize the visited array.
            visited = new boolean[n+1];
            blacklistedEdge = curr;

            // Node 1 will always be the origin of the first tree
            // Then calculate the distance of the tree
            int furthest1 = getFurthest(1);

            int diameter1 = getDiameter(furthest1);
            int radius1 = (diameter1 + 1) / 2;

            // We see which node is not visited, and do DFS from there
            int i;
            for (i = 1; i <= n; ++i){
                if (visited[i]) continue;
                break;
            }

            int furthest2 = getFurthest(i);
            int diameter2 = getDiameter(furthest2);

            int radius2 = (diameter2 + 1) / 2;

            // Remember to ensure that the leftover trees are not huge
            int newDiameter = radius1 + radius2 + 1;
            int bestDiameter = Math.max(Math.max(diameter2, diameter1), newDiameter);

            if (bestDiameter < best){
                best = bestDiameter;
                removedEdge = curr;

                int start = getMidpoint(furthest1, radius1);
                int end = getMidpoint(furthest2, radius2);
                inputEdge = new Edge(start, end);
            }
        }

        // Print that shit
        System.out.println(best);
        System.out.printf("%d %d\n", removedEdge.getStart(), removedEdge.getEnd());
        System.out.printf("%d %d\n", inputEdge.getStart(), inputEdge.getEnd());
    }

    public static void main(String[] args) throws IOException{
        FlightPlanning solution = new FlightPlanning();
        solution.run();
    }
}

