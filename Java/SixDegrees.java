import java.io.*;
import java.util.*;

class Pair{
    int node;
    int distance;

    public Pair(int node, int distance){
        this.node = node;
        this.distance = distance;
    }
}

public class SixDegrees{
    HashMap<String, Integer> mapping = new HashMap<>();
    LinkedList<Pair> bfs;
    ArrayList<ArrayList<Integer>> adjList = new ArrayList<>();

    // Function to map a string to a node number
    private int getMapping(String str){
        if (mapping.containsKey(str)){
            return mapping.get(str);
        }

        // If the string is not in the mapping, add it in and add a new arrayList
        // for that particular pairing.
        mapping.put(str, mapping.size());
        adjList.add(new ArrayList<>());
        return mapping.size()-1;
    }

    // We'll just do BFS n times. 3000 * 30000 = 90M. Nyeeh
    private int bfs(int node){
        boolean[] visited = new boolean[mapping.size()];
        bfs = new LinkedList<>();
        bfs.addFirst(new Pair(node, 0));
        visited[node] = true;

        while (!bfs.isEmpty()){
            Pair current = bfs.pollLast();

            // If we have > 6 degrees, break!
            if (current.distance > 6) return 1;

            // Do BFS
            for (int neighbour : adjList.get(current.node)){
                if (visited[neighbour]) continue;
                visited[neighbour] = true;
                bfs.addFirst(new Pair(neighbour, current.distance+1));
            }
        }

        // If we reached here, we BFS'ed everything and found that everyone < 6!
        // Yay, return 0 so we don't add to the head count.
        return 0;
    }

    private void run(BufferedReader r) throws IOException{
        // Scan in input
        int m = Integer.parseInt(r.readLine());
        for (int i = 0; i < m; ++i){
            String[] dlist = r.readLine().split(" +");

            int start = getMapping(dlist[0]);
            int end = getMapping(dlist[1]);

            // By here, the number of ArrayLists in adjList would not have AIOOB
            adjList.get(start).add(end);
            adjList.get(end).add(start);
        }

        // OK we will be doing BFS.
        int numFail = 0;
        for (int i = 0; i < mapping.size(); ++i){
            numFail += bfs(i);
        }

        // Is it too many?
        if (numFail * 20 > mapping.size()) System.out.println("NO");
        else System.out.println("YES");
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());
        for (int i = 0; i < testcases; ++i){
            SixDegrees sixdegrees = new SixDegrees();
            sixdegrees.run(r);
        }
    }
}
