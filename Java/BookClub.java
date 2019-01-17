import java.io.*;
import java.util.*;

public class BookClub{
    private ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();
    private int[] backwardConnection;
    private int[] forwardConnection;
    private boolean[] visited;

    private boolean dfs(int node){
        if (visited[node]) return false;
        visited[node] = true;

        // DFS each neighbour only if I can augment the path from it.
        for (int neighbour : adjList.get(node)){
            if (backwardConnection[neighbour] == -1){
                backwardConnection[neighbour] = node;
                forwardConnection[node] = neighbour;
                return true;
            }

            // If we cannot dfs, we just continue;
            if (!dfs(backwardConnection[neighbour])) continue;

            backwardConnection[neighbour] = node;
            forwardConnection[node] = neighbour;
            return true;
        }

        // If we reached here, we cannot augment anymore :<
        return false;
    }

    private String run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");

        int N = Integer.parseInt(dlist[0]);
        int M = Integer.parseInt(dlist[1]);

        for (int i = 0; i < N; ++i){
            adjList.add(new ArrayList<>());
        }

        forwardConnection = new int[N];
        backwardConnection = new int[N];

        // Scan in edges
        for (int i = 0; i < M; ++i){
            String[] ph = r.readLine().split(" ");
            int start = Integer.parseInt(ph[0]);
            int end = Integer.parseInt(ph[1]);
            adjList.get(start).add(end);
        }

        // Initialise forwards and backwards connections
        for (int i = 0; i < N; ++i){
            forwardConnection[i] = -1;
            backwardConnection[i] = -1;
        }

        // Deterministically assign books from the right to the left.
        // Look through the list of neighbours for each book, and try to assign the
        // book to the first neighbour that is not visited yet.
        for (int i = 0; i < N; ++i){
            for (int neighbour : adjList.get(i)){
                if (backwardConnection[neighbour] != -1) continue;
                forwardConnection[i] = neighbour;
                backwardConnection[neighbour] = i;
                break;
            }
        }

        for (int i = 0; i < N; ++i){
            visited = new boolean[N];
            if (forwardConnection[i] != -1) continue;
            if (!dfs(i)) return "NO";
        }

        return "YES";
    }

    public static void main(String[] args) throws IOException{
        BookClub bookClub = new BookClub();
        System.out.println(bookClub.run());
    }
}
