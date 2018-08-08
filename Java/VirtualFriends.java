import java.io.*;
import java.util.*;

class Onion{
    int[] onion;
    int[] size;

    // Constructor
    public Onion (int n){
        onion = new int[n];
        size = new int[n];
        for (int i = 0; i < n; ++i){
            onion[i] = i;
            size[i] = 1;
        }
    }

    private int find(int x){
        if (onion[x] != x){
            onion[x] = this.find(onion[x]);
        }
        return onion[x];
    }

    public void onion(int x, int y){
        int parenta = this.find(x);
        int parentb = this.find(y);
        if (parenta != parentb){
            onion[parentb] = parenta;
            size[parenta] += size[parentb];
        }
    }

    // Returns the size of the component of element x
    public int getSize(int x){
        return this.size[find(x)];
    }
}

public class VirtualFriends{
    public void run (BufferedReader r, OutputStream log) throws IOException{
        HashMap<String, Integer> mapping = new HashMap<>();
        int numPeople = 0;
        int n = Integer.parseInt(r.readLine());

        // We need to do this offline
        int[][] memory = new int[n][2];

        // Scan in the input
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            if (mapping.containsKey(dlist[0])){
                memory[i][0] = mapping.get(dlist[0]);
            }
            else {
                mapping.put(dlist[0], numPeople);
                memory[i][0] = numPeople++;
            }
            if (mapping.containsKey(dlist[1])){
                memory[i][1] = mapping.get(dlist[1]);
            }
            else {
                mapping.put(dlist[1], numPeople);
                memory[i][1] = numPeople++;
            }
        }

        Onion onion = new Onion(numPeople);

        // Process the values, then flush the output
        for (int i = 0; i < n; ++i){
            onion.onion(memory[i][0], memory[i][1]);
            log.write(String.valueOf(onion.getSize(memory[i][0])).getBytes());
            log.write('\n');
            log.flush();
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);
        VirtualFriends solution = new VirtualFriends();
        int testcases = Integer.parseInt(r.readLine());
        while (testcases > 0){
            solution.run(r, log);
            testcases--;
        }
    }
}
