import java.io.*;
import java.util.*;


public class ElementaryMath{
    HashMap<Integer, ArrayList<Integer>> adjMap = new HashMap<>();
    HashMap<Long, Integer> mapping = new HashMap<>();
    HashMap<Integer, Long> reverse = new HashMap<>();
    int count = 0;

    long[][] input = new long[2505][2];
    int[] forward = new int[7505];
    int[] backward = new int[7505];
    boolean[] visited;

    private int dfs (int x){
        if (visited[x]) return 0;
        visited[x] = true;

        for (int neighbor : adjMap.get(x)){
            if (backward[neighbor] == -1){
                forward[x] = neighbor;
                backward[neighbor] = x;
                return 1;
            }
            
            // Go deeper
            if (dfs(backward[neighbor]) == 0) continue;

            forward[x] = neighbor;
            backward[neighbor] = x;
            return 1;
        }

        return 0;
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine()); 

        // Reset the values
        for (int i = 0; i < n; ++i){
            forward[i] = -1;
        }

        for (int i = 0; i < 3*n; ++i){
            backward[i] = -1;
        }

        for (int i = 0; i < n; ++i){
            adjMap.put(i, new ArrayList<>());

            String[] dlist = r.readLine().split(" ");
            long a = Long.parseLong(dlist[0]);
            long b = Long.parseLong(dlist[1]);
            input[i][0] = a;
            input[i][1] = b;

            // Find the possible answers
            long ans1 = a + b;
            long ans2 = a - b;
            long ans3 = a * b;

            if (!mapping.containsKey(ans1)){
                mapping.put(ans1, count);
                reverse.put(count, ans1);
                count++;
            }

            adjMap.get(i).add(mapping.get(ans1));

            if (!mapping.containsKey(ans2)){
                mapping.put(ans2, count);
                reverse.put(count, ans2);
                count++;
            }

            adjMap.get(i).add(mapping.get(ans2));

            if (!mapping.containsKey(ans3)){
                mapping.put(ans3, count);
                reverse.put(count, ans3);
                count++;
            }

            adjMap.get(i).add(mapping.get(ans3));
        }

        // We will do MCBM, prepopulate the matches
        int matches = 0;
        for (int i = 0; i < n; ++i){
            for (int neighbor : adjMap.get(i)){
                if (backward[neighbor] == -1){
                    backward[neighbor] = i;
                    forward[i] = neighbor;
                    ++matches;
                    break;
                }
            }
        }

        // Do MCBM here
        for (int i = 0; i < n; ++i){
            if (forward[i] != -1) continue;
            visited = new boolean[n];
            matches += dfs(i);
        }

        // Time to output
        if (matches != n){
            System.out.println("impossible");
            return;
        }

        for (int i = 0; i < n; ++i){
            long ans = reverse.get(forward[i]);
            long a = input[i][0];
            long b = input[i][1];
            if (a + b == ans){
                System.out.printf("%d + %d = %d\n", a, b, ans);
            }
            else if (a - b == ans){
                System.out.printf("%d - %d = %d\n", a, b, ans);
            }
            else { // if (a * b == ans)
                System.out.printf("%d * %d = %d\n", a, b, ans);
            }
        }
    }
    
    public static void main(String[] args) throws IOException{
        ElementaryMath elementary = new ElementaryMath();
        elementary.run();
    }
}

