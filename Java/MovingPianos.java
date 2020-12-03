import java.io.*;
import java.util.*;

class FlowEdge {
    int capacity;
    int flow;

    public FlowEdge(int capacity){
        this.capacity = capacity;
        this.flow = 0;
    }

    public int residual(){
        return this.capacity - this.flow;
    }
}

class FF {
    HashMap<Integer, HashMap<Integer, FlowEdge>> adjlist = new HashMap<>();
    boolean[] visited;

    int SOURCE;
    int SINK;
    int n;
    int numPianos;
    int numMovers;
    int flow = 0;

    public FF (int m, int p){
        numPianos = m;
        numMovers = p/2;

        for (int i = 0; i < m + 102; ++i){
            adjlist.put(i, new HashMap<>());
        }

        SOURCE = 0;
        SINK = m + 101;
        n = m + 102;

        // Set up flow to all my pianos
        for (int i = 1; i <= numPianos; ++i){
            adjlist.get(SOURCE).put(i, new FlowEdge(1));
            adjlist.get(i).put(SOURCE, new FlowEdge(0));
        }
    }

    public void weekday(){
        for (int i = 1; i <= 5; ++i){
            for (int j = i; j <= 100; j += 7){
                adjlist.get(numPianos + j).put(SINK, new FlowEdge(numMovers));
                adjlist.get(SINK).put(numPianos + j, new FlowEdge(0));
            }
        }
    }

    public void weekend(){
        for (int i = 6; i <= 7; ++i){
            for (int j = i; j <= 100; j += 7){
                adjlist.get(numPianos + j).put(SINK, new FlowEdge(numMovers));
                adjlist.get(SINK).put(numPianos + j, new FlowEdge(0));
            }
        }
    }

    public void addEdgePiano(int piano, int start, int end){
        for (int day = start; day <= end; ++day){
            adjlist.get(piano).put(numPianos + day, new FlowEdge(1));
            adjlist.get(numPianos + day).put(piano, new FlowEdge(0));
        }   
    }

    private int dfs(int node, int flow){
        if (node == SINK) return flow;
        visited[node] = true;

        for (int neighbor : adjlist.get(node).keySet()){
            if (visited[neighbor]) continue;

            FlowEdge edge = adjlist.get(node).get(neighbor);
            int newFlow = Math.min(flow, edge.residual());

            if (newFlow == 0) continue;
            newFlow = dfs(neighbor, newFlow);

            if (newFlow > 0){
                edge.flow += newFlow;
                adjlist.get(neighbor).get(node).flow -= newFlow;
                return newFlow;
            }
        }

        return 0;
    }

    private int dfs(int node){
        visited = new boolean[n];
        return dfs(node, 65537);
    }

    public int getFlow(){
        int out = dfs(SOURCE);
        while (out > 0){
            flow += out;
            out = dfs(SOURCE);
        }
        return flow;
    }
}

public class MovingPianos{

    private void solve(BufferedReader r) throws IOException {
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int m = Integer.parseInt(dlist[0]);
        int p = Integer.parseInt(dlist[1]);

        // Create the FF graph and initialize to weekday mode
        FF ff = new FF(m, p);
        ff.weekday();

        for (int i = 1; i <= m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            ff.addEdgePiano(i, start, end);
        }

        int flow = ff.getFlow();

        if (flow == m){
            System.out.println("fine");
            return;
        }

        // Set up for weekend mode
        ff.weekend();
        flow = ff.getFlow();

        if (flow == m){
            System.out.println("weekend work");
        }
        else {
            System.out.println("serious trouble");
        }
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());

        for (int i = 0; i < testcases; ++i){
            solve(r);
        }
    }

    public static void main(String[] args) throws IOException{
        MovingPianos pianos = new MovingPianos();
        pianos.run();
    }
}
