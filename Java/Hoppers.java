import java.io.*;
import java.util.*;

class Onion{
    int[] Onion;
    int components;
    
    public Onion(int n){
        Onion = new int[n+1];
        for (int i = 1; i <= n; ++i){
            Onion[i] = i;
        }
        components = n;
    }

    public int find(int x){
        if (Onion[x] != x){
            Onion[x] = find(Onion[x]);
        }
        return Onion[x];
    }

    public void onion(int x, int y){
        int parentx = this.find(x);
        int parenty = this.find(y);

        if (parentx != parenty){
            Onion[parentx] = parenty;
            components--;
        }
    }
    
    public int getNumComponents(){
        return components;
    }
}

public class Hoppers{
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    int[] visited;
    boolean odd = false;

    private void dfs(int curr, int step){
        visited[curr] = step;

        for (int neighbor : adjlist.get(curr)){
            // Do we have a cycle?
            if (visited[neighbor] != 0){
                if ((step - visited[neighbor]) % 2 == 0){
                    odd = true;
                    return;
                }
            }
            else {
                dfs(neighbor, step+1);
            }
        }
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Initialize my ONION and adjlist
        Onion onion = new Onion(n);
        visited = new int[n+1];
        for (int i = 0; i <= n; ++i){
            adjlist.add(new ArrayList<>());
        }

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            adjlist.get(start).add(end);
            adjlist.get(end).add(start);

            // Onion these two components together too
            onion.onion(start, end);
        }
        
        // OK now we need to see if there is an odd cycle.
        // If there we, we can connect everyone together with components-1 edges.
        // If not, we need to spend one edge to create that odd cycle
        for (int i = 1; i <= n; ++i){
            if (visited[i] != 0) continue;
            dfs(i, 1);
            if (odd) break;
        }

        // Print that shit
        int out = onion.getNumComponents();
        if (odd) out--;
        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        Hoppers hopper = new Hoppers();
        hopper.run();
    }
}
