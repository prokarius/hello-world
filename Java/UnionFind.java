import java.util.*;
import java.io.*;

// Onion class
class Onion{
    private int[] onion;

    public Onion(int n){
        onion = new int[n];
        for (int i = 0; i < n; ++i){
            onion[i] = i;
        }
    }

    private int find (int x){
        if (onion[x] != x){
            onion[x] = find(onion[x]);
        }
        return onion[x];
    }

    public void union(int a, int b){
        int parenta = this.find(a);
        int parentb = this.find(b);
        if (parenta != parentb){
            onion[parenta] = parentb;
        }
    }

    public boolean check(int a, int b){
        return find(a) == find(b);
    }
}

public class UnionFind{
    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] phlist = r.readLine().split(" ");
        int n = Integer.parseInt(phlist[0]);
        int k = Integer.parseInt(phlist[1]);
        Onion onion = new Onion(n);

        // Set up fast output
        OutputStream log = new BufferedOutputStream(System.out);

        for (int i = 0; i < k; ++i){
            String[] dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[1]);
            int y = Integer.parseInt(dlist[2]);
            if (dlist[0].equals("?")){
                log.write((onion.check(x, y)?"yes":"no").getBytes());
                log.write('\n');
            }
            else{ // dlist[0] == '='
                onion.union(x,y);
            }
        }
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        UnionFind onion = new UnionFind();
        onion.run();
    }
}
