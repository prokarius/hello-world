import java.util.*;

public class PachinkoProb{
    static ArrayList<Integer> topo = new ArrayList<>();
    static ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();
    static ArrayList<Integer> gates = new ArrayList<>();
    static int[] visited;
    static int[] invertex; // Stores number of in arrows
    static long[] balls;
    static long total = 0;
    static long winning = 0;

    public static void main(String[] args){
        // Scan in input
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        int m = s.nextInt();

        // Make the adjList and visited and balls array
        for (int i=0; i<n; ++i){
            adjList.add(new ArrayList<>());
        }
        visited = new int[n];
        invertex = new int[n];
        balls = new long[n];

        // Populate the adjList
        for (int i=0; i<m; ++i){
            int start = s.nextInt();
            int end = s.nextInt();
            adjList.get(start).add(end);
            invertex[end]++;
        }

        // Populate the gate
        int k = s.nextInt();
        for (int i=0; i<k; ++i){
            int gate = s.nextInt();
            gates.add(gate);
        }

        // Toposort the thing
        // Add the initial balls while we are at it
        for (int i=0; i<n; ++i){
            if (visited[i] == 0){
                toposort(i);
            }
            if (invertex[i] == 0){
                balls[i] = 1;
            }
        }

        // Then simulate the balls dropping
        for (int l=n-1; l>=0; --l){
            int i = topo.get(l);
            for (int j : adjList.get(i)){
                balls[j] += balls[i];
            }
        }

        // Count the number of balls
        for (int i : gates){
            winning += balls[i];
        }

        for (int i=0; i<n; ++i){
            if (adjList.get(i).size() == 0){
                total += balls[i];
            }
        }

        // Print
        System.out.printf("winning paths %d\ntotal paths %d\n", winning, total);
    }

    private static void toposort(int vertex){
        // Set vertex to true
        visited[vertex] = 1;

        // For each guy, if we have not added him before, add him
        for (int i : adjList.get(vertex)){
            if (visited[i] == 0){
                toposort(i);
            }
        }
        topo.add(vertex);
    }
}
