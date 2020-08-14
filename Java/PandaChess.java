import java.io.*;
import java.util.*;

public class PandaChess{

    HashMap<Long, Integer> mapping = new HashMap<>(150000);
    HashMap<Integer, Integer> revMapping = new HashMap<>(150000);
    int mappingSize = 0;

    boolean[] visited;
    LinkedList<Integer> toposort = new LinkedList<>();

    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();

    private int getID(long x){
        if (mapping.containsKey(x)){
            return mapping.get(x);
        }
        mapping.put(x, mappingSize);
        mappingSize++;
        return mappingSize - 1;
    }

    private void dfs(int node){
        visited[node] = true;
        for (int neighbor : adjlist.get(node)){
            if (visited[neighbor]) continue;
            dfs(neighbor);
        }
        toposort.addFirst(node);
    }

    private void run() throws IOException{ 
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Set up my data structures
        visited = new boolean[n];
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        for (int i = 0; i < m; ++i){ 
            dlist = r.readLine().split(" ");
            int start = getID(Long.parseLong(dlist[0]));
            int end = getID(Long.parseLong(dlist[1]));

            // Create the adjlist 
            adjlist.get(start).add(end);
        }

        // Cool, create the toposort
        for (int i = 0; i < n; ++i){
            if (visited[i]) continue;
            dfs(i);
        }

        // Cool, so now we have the reverse mapping.
        int count = 0;
        for (int i : toposort){
            revMapping.put(i, count);
            count++;
        }

        // Scan in the rankings
        int[] array = new int[n];
        int toDelete = 0;
        count = 0;
        for (int i = 0; i < n; ++i){
            Integer panda = mapping.get(Long.parseLong(r.readLine()));

            // There is a possiblilty panda is not defined.
            // Since the order is well defined, if panda doesn appear => no such person.
            if (panda == null) {
                toDelete++;
                continue;
            }

            array[count] = revMapping.get(panda);
            count++;
        }

        // Reset the LISArray
        int[] LIS = new int[count+1];
        for (int i = 1; i < count; ++i){
            LIS[i] = 1<<30;
        }
        LIS[0] = -1;


        // Do LIS
        int LISLength = 0;
        for (int i = 0; i < count; ++i){
            int lo = 0;
            int hi = LISLength;

            while (lo < hi){
                int mid = (lo+hi)/2;
                if (LIS[mid] < array[i]){ 
                    lo = mid + 1;
                }
                else {
                    hi = mid;
                }
            }

            if (hi == LISLength){
                LISLength++;
            }

            LIS[hi] = array[i];
        }

        // You need to delete the things not part of LIS
        toDelete += count - LISLength;

        // Cool, what is n - LISLength, twice that is the number of adds needed
        int toAdd = n - LISLength;
        System.out.println(toAdd + toDelete);
    }

    public static void main(String[] args) throws IOException{
        PandaChess pandachess = new PandaChess();
        pandachess.run();
    }
}

