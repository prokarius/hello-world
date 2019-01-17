import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    private int end;
    private double weight;

    public Edge (int vertex, double weight){
        this.end = vertex;
        this.weight = weight;
    }

    public int getEnd(){
        return this.end;
    }

    public double getWeight(){
        return this.weight;
    }

    public int compareTo(Edge other){
        return ((this.weight < other.weight) ? 1 : 0) - ((other.weight < this.weight) ? 1 : 0);
    }
}

public class GetShorty{
    private void run(int N, int M, BufferedReader r) throws IOException{
        // Set up the DS
        double[] distance = new double[N];
        PriorityQueue<Edge> pqueue = new PriorityQueue<>();
        ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();

        for (int i=0; i<N; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Scan in input
        for (int i=0; i<M; ++i){
            String[] input = r.readLine().split(" ");
            int start = Integer.parseInt(input[0]);
            int end = Integer.parseInt(input[1]);
            double weight = Double.parseDouble(input[2]);

            // Lets not even bother considering if he'll die passing through
            if (weight == 0){
                continue;
            }

            adjlist.get(start).add(new Edge(end, weight));
            adjlist.get(end).add(new Edge(start, weight));
        }

        // dijkstra from the start
        pqueue.add(new Edge(0, 1));

        while (!pqueue.isEmpty()){
            Edge curr = pqueue.poll();
            if (curr.getWeight() <= distance[N-1]){
                break;
            }
            if (curr.getWeight() < distance[curr.getEnd()]){
                continue;
            }
            for (Edge edge : adjlist.get(curr.getEnd())){
                int neighbour = edge.getEnd();
                if (distance[neighbour] < edge.getWeight() * curr.getWeight()){
                    distance[neighbour] = edge.getWeight() * curr.getWeight();
                    pqueue.add(new Edge(neighbour, distance[neighbour]));
                }
            }
        }

        System.out.println(String.format("%.4f", distance[N-1]));
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] nandm = r.readLine().split(" ");
        int N = Integer.parseInt(nandm[0]);
        int M = Integer.parseInt(nandm[1]);
        while (N != 0 && M != 0){
            GetShorty getshorty = new GetShorty();
            getshorty.run(N, M, r);
            nandm = r.readLine().split(" ");
            N = Integer.parseInt(nandm[0]);
            M = Integer.parseInt(nandm[1]);
        }
    }
}
