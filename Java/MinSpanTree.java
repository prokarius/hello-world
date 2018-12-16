import java.io.*;
import java.util.*;

// For UFDS
class Onion {
    private int[] onion;

    public Onion (int n){
        this.onion = new int[n];
        for (int i = 0; i < n; ++i){
            onion[i] = i;
        }
    }

    private int find(int x){
        if (x != this.onion[x]){
            this.onion[x] = find(this.onion[x]);
        }
        return this.onion[x];
    }

    // Union
    public void onion(int x, int y){
        int xParent = find(x);
        int yParent = find(y);
        this.onion[xParent] = yParent;
    }

    public boolean isSameSet(int x, int y){
        return find(x) == find(y);
    }
}

class Edge implements Comparable<Edge>{
    private int start;
    private int end;
    private int weight;

    public Edge(int start, int end, int weight){
        this.start = start;
        this.end = end;
        this.weight = weight;
    }

    public int getStart(){
        return this.start;
    }

    public int getEnd(){
        return this.end;
    }

    public int getWeight(){
        return this.weight;
    }

    public int compareTo(Edge other){
        if (this.weight == other.weight){
            if (this.start == other.start){
                return (this.end - other.end);
            }
            return (this.start - other.start);
        }
        return (this.weight - other.weight);
    }

    public int cmpByStart(Edge other){
        if (this.start == other.start){
            return this.end - other.end;
        }
        return this.start - other.start;
    }
}

// We implement Kruskal's.
// Easier than Prims I feel.
public class MinSpanTree{
    public void run(int n, int m, BufferedReader r, OutputStream log) throws IOException{
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        ArrayList<Edge> output = new ArrayList<>();
        Onion onion = new Onion(n);
        int totalWeight = 0;

        for (int i = 0; i < m; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            // Swap the edges around if end is bigger
            if (end < start){
                end = end ^ start;
                start = end ^ start;
                end = end ^ start;
            }

            int weight = Integer.parseInt(dlist[2]);
            pq.add(new Edge(start, end, weight));
        }

        // Pop from the pq and union the edges
        n--;
        while (pq.size() > 0){
            if (n == 0) break;
            Edge curr = pq.poll();
            int start = curr.getStart();
            int end = curr.getEnd();
            if (!onion.isSameSet(start, end)){
                output.add(curr);
                onion.onion(start, end);
                totalWeight += curr.getWeight();
                n--;
            }
        }

        // If we didn't take enough edges, we say it's Impossible.
        if (n > 0) {
            log.write("Impossible\n".getBytes());
            log.flush();
            return;
        }

        // Sort the output
        Collections.sort(output, (Edge e1, Edge e2) -> e1.cmpByStart(e2));

        // Print the weight and edges
        log.write(String.valueOf(totalWeight).getBytes());
        log.write('\n');
        for (Edge edge: output){
            log.write(String.valueOf(edge.getStart()).getBytes());
            log.write(' ');
            log.write(String.valueOf(edge.getEnd()).getBytes());
            log.write('\n');
        }
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);
        MinSpanTree solution = new MinSpanTree();
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);
        while (n != 0 || m != 0){
            solution.run(n, m, r, log);
            dlist = r.readLine().split(" ");
            n = Integer.parseInt(dlist[0]);
            m = Integer.parseInt(dlist[1]);
        }
    }
}
