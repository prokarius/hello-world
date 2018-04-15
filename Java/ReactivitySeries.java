import java.util.*;
import java.io.*;

public class ReactivitySeries{
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    ArrayList<Boolean> visited = new ArrayList<>();
    LinkedList<Integer> toposort = new LinkedList<>();

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] nandk = r.readLine().split(" ");
        int n = Integer.parseInt(nandk[0]);
        int k = Integer.parseInt(nandk[1]);
        for (int i=0; i<n; ++i){
            adjlist.add(new ArrayList<>());
            visited.add(false);
        }

        // Make the adjlist
        for (int i=0; i<k; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);
            adjlist.get(start).add(end);
        }

        // Do a toposort
        for (int i=0; i<n; ++i){
            if (!visited.get(i)){
                tsort(i);
            }
        }

        // Now toposort contains toposorted elements.
        // Check for uniqueness by comparing each neighbour elements
        boolean notunique = false;
        for (int i=0; i<n-1; ++i){
            if (adjlist.get(toposort.get(i)).indexOf(toposort.get(i+1)) == -1){
                notunique = true;
                break;
            }
        }

        // Print
        if (notunique){
            System.out.println("back to the lab");
        }
        else {
            for (int i=0; i<toposort.size(); ++i){
                System.out.printf("%d", toposort.get(i));
                if (i != toposort.size()-1){
                    System.out.printf(" ");
                }
            }
            System.out.printf("\n");
        }
    }

    private void tsort(int vertex){
        visited.set(vertex, true);
        for (int neighbour : adjlist.get(vertex)){
            if (!visited.get(neighbour)){
                tsort(neighbour);
            }
        }
        toposort.addFirst(vertex);
    }

    public static void main(String[] args) throws IOException{
        ReactivitySeries solution = new ReactivitySeries();
        solution.run();
    }
}
