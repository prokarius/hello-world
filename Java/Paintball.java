import java.io.*;
import java.util.*;

public class Paintball{

    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();

    int[] forwards;
    int[] backwards;
    boolean[] visited;

    private boolean dfs(int curr){
        if (visited[curr]) return false;
        visited[curr] = true;

        for (int neighbor : adjlist.get(curr)){
            if (backwards[neighbor] == -1){
                backwards[neighbor] = curr;
                forwards[curr] = neighbor;
                return true;
            }

            if (!dfs(backwards[neighbor])) continue;

            backwards[neighbor] = curr;
            forwards[curr] = neighbor;
            return true;
        }

        return false;
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        forwards = new int[n];
        backwards = new int[n];
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());

            forwards[i] = -1;
            backwards[i] = -1;
        }

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]) - 1;
            int end = Integer.parseInt(dlist[1]) - 1;

            adjlist.get(start).add(end);
            adjlist.get(end).add(start);
        }

        // Do MCBM
        // Initialize everyone with a forward edge if they can
        for (int i = 0; i < n; ++i){
            // Premature: If a player can't see anyone, it's impossible
            if (adjlist.get(i).size() == 0){
                System.out.println("Impossible");
                return;
            }

            for (int neighbor : adjlist.get(i)){
                if (backwards[neighbor] != -1) continue;
                forwards[i] = neighbor;
                backwards[neighbor] = i;
                break;
            }
        }

        // For each person, if he isn't hit yet, find an augmenting path
        for (int i = 0; i < n; ++i){
            if (forwards[i] != -1) continue;
            visited = new boolean[n];
            if (!dfs(i)){
                System.out.println("Impossible");
                return;
            }
        }

        // OK it is possible! print
        for (int i = 0; i < n; ++i){
            System.out.println(forwards[i] + 1); // 1-BASED GDMN
        }
    }

    public static void main(String[] args) throws IOException{
        Paintball paintball = new Paintball();
        paintball.run();
    }
}

