import java.io.*;
import java.util.*;

class Edge implements Comparable<Edge>{
    private int start;
    private int end;
    private int cost;

    public Edge(int start, int end, int cost){
        this.start = start;
        this.end = end;
        this.cost = cost;
    }

    public int getStart(){
        return this.start;
    }

    public int getEnd(){
        return this.end;
    }

    public int getCost(){
        return this.cost;
    }

    public int compareTo(Edge other){
        return this.cost - other.cost;
    }
}

public class BlockCrusher{
    private int h;
    private int w;

    private final int[] dr = {0, 1,  1, 0, -1, -1, 1, -1, 0};

    public BlockCrusher(int h, int w){
        this.h = h;
        this.w = w;
    }

    private void run(BufferedReader r, OutputStream log) throws IOException{
        // Scan in input
        int[][] grid = new int[h][w];
        for (int i = 0; i < h; ++i){
            String str = r.readLine();
            for (int j = 0; j < w; ++j){
                grid[i][j] = str.charAt(j) - '0';
            }
        }

        // Make the adjlist. Index each square as r*w + c
        ArrayList<ArrayList<Edge>> adjList = new ArrayList<>();

        for (int i = 0; i < h*w; ++i){
            adjList.add(new ArrayList<>());
        }

        // Moving to a neighbour square costs that neighbour's value
        for (int row = 0; row < h; ++row){
            for (int col = 0; col < w; ++col){
                int currCell = row*w + col;

                for (int i = 0; i < 8; ++i){
                    int newr = row + dr[i];
                    int newc = col + dr[i+1];

                    // If we are out of bounds move on
                    if (newr < 0 || newr >= h || newc < 0 || newc >= w) continue;

                    int newCell = newr*w + newc;
                    adjList.get(currCell).add(new Edge(currCell, newCell, grid[newr][newc]));
                }
            }
        }

        // Create a super source and a super sink.
        // Super source connects to the top row
        // Super sink connects to the bottom row
        adjList.add(new ArrayList<>());
        adjList.add(new ArrayList<>());

        for (int col = 0; col < w; ++col){
            adjList.get(h*w).add(new Edge(h*w, col, grid[0][col]));
            adjList.get((h-1)*w + col).add(new Edge((h-1)*w + col, h*w + 1, 0));
        }

        // Do Dijkstra
        // Set up the data structures
        int[] parent = new int[h*w + 2];
        int[] cost = new int[h*w + 2];

        for (int i = 0; i < h*w + 2; ++i){
            cost[i] = 1<<30;
        }

        cost[h*w] = 0;

        PriorityQueue<Edge> dijkstra = new PriorityQueue<>();
        dijkstra.add(new Edge(-1, h*w, 0));

        while (!dijkstra.isEmpty()){
            Edge edge = dijkstra.poll();

            int curr = edge.getEnd();
            int currCost = edge.getCost();

            // If we are here with a cheaper way, pass
            if (cost[curr] < currCost) continue;

            for (Edge next : adjList.get(curr)){
                int neighbour = next.getEnd();
                int neighbourCost = currCost + next.getCost();

                // If we visited the neighbor before, skip
                if (cost[neighbour] < neighbourCost) continue;
                cost[neighbour] = neighbourCost;
                parent[neighbour] = curr;

                dijkstra.add(new Edge(curr, neighbour, neighbourCost));
            }
        }

        // Now that we have reached the end, regeneate the path
        int curr = h*w + 1;
        int prev = parent[curr];

        while (prev != h*w){
            int row = prev / w;
            int col = prev % w;

            grid[row][col] = 0;
            curr = prev;
            prev = parent[curr];
        }

        // Finally, we can print
        for (int i = 0; i < h; ++i){
            for (int j = 0; j < w; ++j){
                if (grid[i][j] == 0) log.write(' ');
                else log.write(String.valueOf(grid[i][j]).getBytes());
            }
            log.write('\n');
        }

        // FLUSH THAT!
        log.write('\n');
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);
        String[] dlist = r.readLine().split(" ");
        int h = Integer.parseInt(dlist[0]);
        int w = Integer.parseInt(dlist[1]);

        while (h != 0 && w != 0){
            BlockCrusher blockCrusher = new BlockCrusher(h, w);
            blockCrusher.run(r, log);
            dlist = r.readLine().split(" ");
            h = Integer.parseInt(dlist[0]);
            w = Integer.parseInt(dlist[1]);
        }
    }
}

