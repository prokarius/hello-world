import java.util.*;
import java.io.*;

class Fenwick{
    // Constructor for a fenwick tree
    int[] fenwick;
    int size;

    public Fenwick(int n){
        fenwick = new int[n+1];
        this.size = n+1;
    }

    private int LSOne(int i){
        return (i & -i);
    }

    public void update(int location, int value){
        while (location < this.size){
            fenwick[location] += value;
            location += LSOne(location);
        }
    }

    public int rsq(int end){
        int sum = 0;
        while (end > 0){
            sum += fenwick[end];
            end -= LSOne(end);
        }
        return sum;
    }

    public int rsq(int start, int end){
        return rsq(end) - rsq(start-1);
    }
}

public class Turbo{
    // private int[] visited;
    private int[] input;
    private int[] output;

    public void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());

        // Create all my data structures
        // visited is the array we are keeping track in the FT.
        // It actually isn't needed, because we do not need to keep track of whoever
        // we have visited before. It's just here to help me with the fenwick tree.
        // visited = new int[n+1];
        input = new int[n];
        output = new int[n+1];
        Fenwick fenwick = new Fenwick(n);

        // Technically we can process the numbers as we read them in. Saves a step...
        for (int i = 0; i < n; ++i){
            input[i] = Integer.parseInt(r.readLine());
        }

        // Look at the each number. Determine the direction its supposed to move
        for (int i = 0; i < n; ++i){
            int curr = input[i];
            if (curr <= (n+1)/2){
                // If we are here, it means the value is supposed to bubble left.
                // Find the range of numbers that it has to look out for
                // High is just n - (curr - 1)
                int low = curr + 1;
                int high = n - (curr - 1);

                // Now from what we have visited, we want to find out how many of
                // them fall in that range. Just call the FT.
                output[curr] = fenwick.rsq(low, high);
            }

            // It is the same for the other case, except the value bubbles right.
            // Take note of the bounds: High is just curr - 1,
            // Low is the number of numbers to n (n - (curr - 1)) + 1.
            else {
                int low = (n - (curr - 1)) + 1;
                int high = curr - 1;

                // The number of things that exist further right equals the number
                // of things to consider minus the number of thing we seen before.
                // = ((high - low) + 1) - number of things we have seen before
                output[curr] = ((high - low) + 1) - fenwick.rsq(low, high);
            }

            // Then lastly, set the visited array to be 1 and update the FT.
            // visited[curr] = 1;
            fenwick.update(curr, 1);
        }

        // Yay, now our output array is updated! We just have to print them out
        // Don't forget the left, right, left, right order
        OutputStream log = new BufferedOutputStream (System.out);
        for (int i = 0; i < n; ++i){
            if (i % 2 == 0){
                log.write(String.valueOf(output[i/2 + 1]).getBytes());
            }
            else {
                log.write(String.valueOf(output[n - i/2]).getBytes());
            }
            log.write('\n');
            log.flush();
        }
    }

    public static void main(String[] args) throws IOException{
        Turbo turbo = new Turbo();
        turbo.run();
    }
}
