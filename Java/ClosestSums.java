import java.io.*;
import java.util.*;

public class ClosestSums{
    private void run(BufferedReader r, int n, int caseNum) throws IOException{
        OutputStream log = new BufferedOutputStream (System.out);

        int[] numbers = new int[n];

        // Scan in input
        for (int i = 0; i < n; ++i){
            numbers[i] = Integer.parseInt(r.readLine());
        }

        // Populate the treeset
        TreeSet<Integer> treeset = new TreeSet<>();

        // Add the sentinel values
        treeset.add(-1000000007);
        treeset.add(1000000007);

        for (int i = 0; i < n-1; ++i){
            for (int j = i+1; j < n; ++j){
                treeset.add(numbers[i] + numbers[j]);
            }
        }

        int queries = Integer.parseInt(r.readLine());

        log.write("Case ".getBytes());
        log.write(String.valueOf(caseNum).getBytes());
        log.write(':');
        log.write('\n');

        for (int i = 0; i < queries; ++i){
            int query = Integer.parseInt(r.readLine());

            // Get the nearest values
            int lower = treeset.floor(query);
            int higher = treeset.ceiling(query);

            log.write("Closest sum to ".getBytes());
            log.write(String.valueOf(query).getBytes());
            log.write(" is ".getBytes());

            // See which one is closer, and print it
            if (query - lower < higher - query){
                log.write(String.valueOf(lower).getBytes());
            }
            else {
                log.write(String.valueOf(higher).getBytes());
            }

            log.write('.');
            log.write('\n');
        }

        // FLUSH
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int caseNum = 1;

        ClosestSums solution = new ClosestSums();

        // Read until EOF
        String n = r.readLine();
        while (n != null){
            solution.run(r, Integer.parseInt(n), caseNum);
            ++caseNum;
            n = r.readLine();
        }
    }
}
