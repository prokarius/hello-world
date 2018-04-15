import java.util.*;
import java.io.*;

class Fenwick{
    int[] fenwick;
    int[] data;
    int n;

    public Fenwick(int n){
        fenwick = new int[n+1];
        data = new int[n+1];
        this.n = n+1;
    }

    private int LSOne(int x){
        return (x&(-x));
    }

    // Flip the bit at index k
    public void update (int k){
        // We need to see what the bit is, act accordingly
        if (data[k] == 1){
            this.update(-1, k);
        }
        else {
            this.update(1, k);
        }

        // Then flip the bit.
        data[k] = 1 - data[k];
    }

    private void update(int v, int k){
        while (k < this.n){
            this.fenwick[k] += v;
            k += LSOne(k);
        }
    }

    private int rsq (int end){
        int sum = 0;
        while (end > 0){
            sum += this.fenwick[end];
            end -= LSOne(end);
        }
        return sum;
    }

    public int rsq (int start, int end){
        return rsq(end) - ((start == 1) ? 0 : rsq(start-1));
    }
}

public class Supercomputer{
    public void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] nandk = r.readLine().split(" ");
        int n = Integer.parseInt(nandk[0]);
        int k = Integer.parseInt(nandk[1]);
        Fenwick fenwick = new Fenwick(n);

        // Run the simultaion
        for (int i=0; i<k; ++i){
            String[] dlist = r.readLine().split(" ");
            if (dlist[0].equals("F")){
                fenwick.update(Integer.parseInt(dlist[1]));
            }
            else{ // dlist[1].equals("C")
                int start = Integer.parseInt(dlist[1]);
                int end = Integer.parseInt(dlist[2]);
                System.out.println(fenwick.rsq(start, end));
            }
        }
    }

    public static void main(String[] args) throws IOException{
        Supercomputer supercomputer = new Supercomputer();
        supercomputer.run();
    }
}
