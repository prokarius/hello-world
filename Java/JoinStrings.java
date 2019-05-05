import java.io.*;
import java.util.*;

public class JoinStrings{
    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        // Scan in input
        int N = Integer.parseInt(r.readLine());

        // Keeps a list of all strings
        String[] strings = new String[N+1];

        for (int i = 1; i <= N; ++i){
            strings[i] = r.readLine();
        }

        // Keep track of the order by using something like an onion array
        int[] links = new int[N+1];
        int[] ending = new int[N+1];
        boolean[] visited = new boolean[N+1];
        for (int i = 1; i <= N; ++i){
            links[i] = i;
            ending[i] = i;
        }

        // Read in the input
        for (int i = 0; i < N-1; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            links[ending[start]] = end;
            ending[start] = ending[end];
            visited[end] = true;
        }

        // Find the starting
        int start = 1;
        while (true){
            if (!visited[start]) break;
            start++;
        }

        // Now start is the starting. We just need to print things out.
        while (start != links[start]){
            log.write(strings[start].getBytes());
            start = links[start];
        }

        // Flush~
        log.write(strings[start].getBytes());
        log.write('\n');
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        JoinStrings solution = new JoinStrings();
        solution.run();
    }
}
