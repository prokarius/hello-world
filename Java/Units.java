import java.io.*;
import java.util.*;

// Because I write really inefficient code unfortunately
class Helper implements Comparable<Helper> {
    String name;
    int value;

    public Helper(String name, int value){
        this.name = name;
        this.value = value;
    }
    
    public int getValue(){
        return this.value;
    }

    public String getName(){
        return this.name;
    }

    public int compareTo(Helper other){
        return this.value > other.value ? 1 : -1;
    }
}

class Edge {
    private int start;
    private int end;
    private int multiplier;
    private boolean direction;

    public Edge (int start, int end, int multiplier, boolean direction){
        this.start = start;
        this.end = end;
        this.multiplier = multiplier;
        this.direction = direction;
    }

    public int getStart(){
        return this.start;
    }

    public int getEnd(){
        return this.end;
    }

    public int getMultiplier(){
        return this.multiplier;
    }

    // Direction flag is set if you multiply to get the conversion factor
    public boolean getDirection(){
        return this.direction;
    }
}

public class Units{
    ArrayList<ArrayList<Edge>> adjlist = new ArrayList<>();

    private void run(BufferedReader r, int n) throws IOException{
        String[] units = r.readLine().split(" ");

        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        // Scan in input
        // For each row, locate the units
        for (int i = 1; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            String unit1 = dlist[0];
            String unit2 = dlist[3];

            int index1 = 0;
            int index2 = 0;

            for (int j = 0; j < n; ++j){
                if (units[j].equals(unit1)){
                    index1 = j;
                }
                if (units[j].equals(unit2)){
                    index2 = j;
                }
            }

            int multiplier = Integer.parseInt(dlist[2]);

            // Create edges to push into our adjlist
            // Also create the reverse edges
            adjlist.get(index1).add(new Edge(index1, index2, multiplier, true));
            adjlist.get(index2).add(new Edge(index2, index1, multiplier, false));
        }

        int[] conversion = new int[n];
        boolean[] visited = new boolean[n];

        // For each one, pretend it is the master
        // (technically n times, but if it's worth doing, it's worth overdoing)
        for (int i = 0; i < n; ++i){
            conversion = new int[n];
            visited = new boolean[n];

            // Reset the conversion array
            for (int j = 0; j < n; ++j){
                conversion[j] = 1;
            }

            // Process the tree as a stack
            LinkedList<Integer> stack = new LinkedList<>();

            // Set the flag if the current unit is not correct
            boolean flag = true;
            stack.push(i);

            while(!stack.isEmpty()){
                int curr = stack.pop();
                visited[curr] = true;
                
                // Try to set the neighbours as directed by the graph.
                // If there is an error, quit and move on
                for (Edge edge : adjlist.get(curr)){
                    int end = edge.getEnd();
                    int start = edge.getStart();
                    int multiplier = edge.getMultiplier();

                    if (visited[end]) continue;

                    // If we are moving forward, then it's fine
                    if (edge.getDirection()){
                        conversion[end] = conversion[start] * multiplier;
                    }

                    else {
                        // If we are moving backwards, if the current cell cannot
                        // divide backwards, then quit
                        if (conversion[start] % multiplier != 0){
                            stack.clear();
                            flag = false;
                            break;
                        }

                        else {
                            conversion[end] = conversion[start] / multiplier;
                        }
                    }
                    stack.push(end);
                }
            }

            // If flag is still true here, break out of the loop to print.
            if (flag) break;
        }

        // Push all the names and conversions into Helper objects, and sort them
        ArrayList<Helper> helper = new ArrayList<>();
        for (int i = 0; i < n; ++i){
            helper.add(new Helper(units[i], conversion[i]));
        }

        Collections.sort(helper);

        // Then print them out
        for (int i = 0; i < n; ++i){
            Helper curr = helper.get(i);
            System.out.printf("%d%s", curr.getValue(), curr.getName());
            if (i != n-1){
                System.out.printf(" = ");
            }
        }

        System.out.println("");
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        
        while (n != 0){
            Units units = new Units();
            units.run(r, n);
            n = Integer.parseInt(r.readLine());
        }
    }
}
