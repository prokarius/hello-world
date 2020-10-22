import java.io.*;
import java.util.*;

class Edge{
    int start;
    int end;

    public Edge(int start, int end){
        this.start = start;
        this.end = end;
    }
}

public class IronCoal{

    ArrayList<ArrayList<Integer>> forwards = new ArrayList<>();
    ArrayList<ArrayList<Integer>> backwards = new ArrayList<>();

    int[] distanceCastle;
    int[] distanceOres;
    int[] distanceCoals;

    Queue<Edge> bfsQueue = new LinkedList<>();

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" "); 
        int n = Integer.parseInt(dlist[0]);
        int o = Integer.parseInt(dlist[1]);
        int c = Integer.parseInt(dlist[2]);

        // Set up my data structures
        int[] ores = new int[o];
        int[] coals = new int[c];

        distanceCastle = new int[n+1];
        distanceOres = new int[n+1];
        distanceCoals = new int[n+1];

        for (int i = 0; i < n; ++i){
            forwards.add(new ArrayList<>());
            backwards.add(new ArrayList<>());
        }

        dlist = r.readLine().split(" "); 
        for (int i = 0; i < o; ++i){
            ores[i] = Integer.parseInt(dlist[i]) - 1;
        }

        dlist = r.readLine().split(" "); 
        for (int i = 0; i < c; ++i){
            coals[i] = Integer.parseInt(dlist[i]) - 1;
        }

        for (int i = 0; i < n; ++i){
            dlist = r.readLine().split(" ");
            int neighbors = Integer.parseInt(dlist[0]);

            for (int j = 1; j <= neighbors; ++j){
                int end = Integer.parseInt(dlist[j]) - 1; // 1 based indexing is a crime
                forwards.get(i).add(end);
                backwards.get(end).add(i);
            }
        }

        // Reset all distances
        for (int i = 0; i < n; ++i){
            distanceCastle[i] = 1<<20;
            distanceOres[i] = 1<<20;
            distanceCoals[i] = 1<<20;
        }

        // TBH I don't know what this is... This is duct tape at its best
        distanceCastle[n] = -1;
        distanceOres[n] = -1;
        distanceCoals[n] = -1;

        // Cool, do BFS forward from the castle
        bfsQueue.add(new Edge(n, 0));

        while (!bfsQueue.isEmpty()){
            Edge e = bfsQueue.remove();
            int start = e.start;
            int end = e.end;

            // Have we been here before?
            if (distanceCastle[end] < 1<<20) continue;

            distanceCastle[end] = distanceCastle[start] + 1;
            for (int neighbor : forwards.get(end)){
                bfsQueue.add(new Edge(end, neighbor));
            }
        }

        // Do BFS from all the iron and coal backwards too
        for (int i = 0; i < o; ++i){
            bfsQueue.add(new Edge(n, ores[i]));
        }

        while (!bfsQueue.isEmpty()){
            Edge e = bfsQueue.remove();
            int start = e.start;
            int end = e.end;

            // Have we been here before?
            if (distanceOres[end] < 1<<20) continue;

            distanceOres[end] = distanceOres[start] + 1;
            for (int neighbor : backwards.get(end)){
                bfsQueue.add(new Edge(end, neighbor));
            }
        }

        for (int i = 0; i < c; ++i){
            bfsQueue.add(new Edge(n, coals[i]));
        }

        while (!bfsQueue.isEmpty()){
            Edge e = bfsQueue.remove();
            int start = e.start;
            int end = e.end;

            // Have we been here before?
            if (distanceCoals[end] < 1<<20) continue;

            distanceCoals[end] = distanceCoals[start] + 1;
            for (int neighbor : backwards.get(end)){
                bfsQueue.add(new Edge(end, neighbor));
            }
        }

        // Awesome, now we just need to find the point that minimizes the sum of the
        // three distances
        int best = 1 << 21;
        for (int i = 0; i < n; ++i){
            best = Math.min(distanceCastle[i] + distanceOres[i] + distanceCoals[i], best);
        }

        if (best >= 1<<20){
            System.out.println("impossible");
        }
        else {
            System.out.println(best);
        }
    }

    public static void main(String[] args) throws IOException{
        IronCoal ironcoal = new IronCoal();
        ironcoal.run();
    }
}

