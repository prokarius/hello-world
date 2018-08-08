import java.io.*;
import java.util.*;


public class Collatz{
    public void run(long x, long y, BufferedOutputStream log) throws IOException{
        // Keep a copy for the BOS
        long copyx = x;
        long copyy = y;

        LinkedList<Long> pathx = new LinkedList<>();
        LinkedList<Long> pathy = new LinkedList<>();

        // Append the two numbers to the end of the deques
        pathx.addLast(x);
        pathy.addLast(y);

        // Then generate the numbers based on collatz conjecture
        while (x != 1){
            if ((x & 1) == 0) x >>= 1;
            else x = x*3 + 1;
            pathx.addLast(x);
        }
        while (y != 1){
            if ((y & 1) == 0) y >>= 1;
            else y = y*3 + 1;
            pathy.addLast(y);
        }

        long output = 1;

        // Now that we have the paths, we keep popping from the front until
        // the front most value differs.
        // Because x and y will definitely reach 1
        while ((pathx.size() > 0) && (pathy.size() > 0) &&
                (pathx.peekLast().equals(pathy.peekLast()))){
            output = pathx.peekLast();
            pathx.pollLast();
            pathy.pollLast();
        }

        // If we are here, it means the front elements are no longer the same
        log.write(String.valueOf(copyx).getBytes());
        log.write(" needs ".getBytes());
        log.write(String.valueOf(pathx.size()).getBytes());
        log.write(" steps, ".getBytes());
        log.write(String.valueOf(copyy).getBytes());
        log.write(" needs ".getBytes());
        log.write(String.valueOf(pathy.size()).getBytes());
        log.write(" steps, they meet at ".getBytes());
        log.write(String.valueOf(output).getBytes());
        log.write("\n".getBytes());
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        BufferedOutputStream log = new BufferedOutputStream(System.out);
        String[] dlist = r.readLine().split(" ");
        long m = Long.parseLong(dlist[0]);
        long n = Long.parseLong(dlist[1]);

        // Keep processing until 0 0
        while ((m > 0) && (n > 0)){
            Collatz collatz = new Collatz();
            collatz.run(m, n, log);
            dlist = r.readLine().split(" ");
            m = Long.parseLong(dlist[0]);
            n = Long.parseLong(dlist[1]);
        }
    }
}
