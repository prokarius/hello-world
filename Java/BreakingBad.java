import java.io.*;
import java.util.*;

public class BreakingBad{
    boolean possible = true;
    HashMap<String, Integer> mapping = new HashMap<>();
    HashMap<Integer, String> reverse = new HashMap<>();

    int[] color;
    ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();

    private void dfs(int n, int currColor){
        color[n] = currColor;

        for (int neighbor : adjList.get(n)){
            // Have we colored it before?
            if (color[neighbor] != 0){
                if (color[neighbor] != 3 - currColor){
                    possible = false;
                    break;
                }
                continue;
            }

            color[neighbor] = 3 - currColor;
            dfs(neighbor, 3 - currColor);
        }
    }

    private void run() throws IOException{ 
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        // Scan in input
        int n = Integer.parseInt(r.readLine());
        color = new int[n];
        for (int i = 0; i < n; ++i){
            adjList.add(new ArrayList<>());
            String item = r.readLine();
            mapping.put(item, i);
            reverse.put(i, item);
        }

        int m = Integer.parseInt(r.readLine());
        for (int i = 0; i < m; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = mapping.get(dlist[0]);
            int end = mapping.get(dlist[1]);
            adjList.get(start).add(end);
            adjList.get(end).add(start);
        }

        // For each item, do DFS
        for (int i = 0; i < n; ++i){
            if (color[i] != 0) continue;
            dfs(i, 1);
        }

        if (!possible){
            System.out.println("impossible");
            return;
        }

        ArrayList<String> walter = new ArrayList<>();
        ArrayList<String> jesse = new ArrayList<>();

        for (int i = 0; i < n; ++i){
            if (color[i] == 1){
                walter.add(reverse.get(i));
            }
            else {
                jesse.add(reverse.get(i));
            }
        }

        for (String item : walter){
            log.write(item.getBytes());
            log.write(' ');
        }
        log.write('\n');

        for (String item : jesse){
            log.write(item.getBytes());
            log.write(' ');
        }
        log.write('\n');

        log.flush();
    }

    public static void main(String[] args) throws IOException{
        BreakingBad breakingBad = new BreakingBad();
        breakingBad.run();
    }
}

