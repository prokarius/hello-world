import java.io.*;
import java.util.*;

public class Dominoes2{

    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    boolean[] visited;
    int out; 

    private void dfs(int node){
        out++;
        visited[node] = true;
        for (int neighbor : adjlist.get(node)){
            if (visited[neighbor]) continue;
            dfs(neighbor);
        }
    }

    private void solve(BufferedReader r) throws IOException{
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);
        int l = Integer.parseInt(dlist[2]);

        // Set up my data structures
        out = 0;
        visited = new boolean[n];
        adjlist.clear();
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]) - 1;
            int end = Integer.parseInt(dlist[1]) - 1;

            adjlist.get(start).add(end);
        }

        // Knock the dominoes over
        for (int i = 0; i < l; ++i){
            int knocked = Integer.parseInt(r.readLine()) - 1;
            if (visited[knocked]) continue;
            dfs(knocked);
        }

        System.out.println(out);
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());

        for (int i = 0; i < testcases; ++i){
            solve(r);
        }
    }

    public static void main(String[] args) throws IOException{
        Dominoes2 dominoes = new Dominoes2();
        dominoes.run();
    }
}

