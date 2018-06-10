import java.util.*;
import java.io.*;

public class IsaHasa{
    HashMap<String, Integer> mapping = new HashMap<>();
    int counter = 0;

    // Returns the Hash value of a given string
    private int getHash(String s){
        if (this.mapping.containsKey(s)){
            return mapping.get(s);
        }
        else {
            mapping.put(s, counter);
            counter++;
            return counter-1;
        }
    }

    public void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] phlist = r.readLine().split(" ");
        int n = Integer.parseInt(phlist[0]);
        int q = Integer.parseInt(phlist[1]);

        // For each relationship
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int hasha = getHash(dlist[0]);
            int hashb = getHash(dlist[2]);

            // If it's a is-a relationship
            if (dlist[1].equals("is-a")){
                //pass
            }
            else { // has-a relationship
                //pass;
            }
        }
    }

    public static void main(String[] args) throws IOException{
        IsaHasa solution = new IsaHasa();
        solution.run();
    }
}
