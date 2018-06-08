import java.util.*;
import java.io.*;

// Fenwick Tree class. Interesting use of a Fenwick Tree.
class FenwickTree{
    int size;
    int[] fenwickTree;

    public FenwickTree(int n){
        this.size = n+1;
        fenwickTree = new int[n+1];
    }

    private int LSOne (int n){
        return n&(-n);
    }

    public void update (int location, int value){
        for (int i = location; i < this.size; i += LSOne(i)){
            fenwickTree[i] += value;
        }
    }

    public int rsq(int end){
        int sum = 0;
        for (int i = end; i>0; i-=LSOne(i)){
            sum += fenwickTree[i];
        }
        return sum;
    }
}

public class MovieCollection{
    int[] output;
    FenwickTree fenwick;
    int[] index;

    private void run(int movies, int requests, BufferedReader r) throws IOException{
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        output = new int[requests];

        // Suppose each of the movies are represented
        // We have a stack that contains either 0 if there exist a movie at that
        // particular position. This will be represented in the fenwick tree.
        // That means that at the start, the stack contains all 1s for the first
        // movie number of positions.

        // When a movie is popped from the stack, we will just leave the space it
        // used to occupy empty. This means that the fenwick tree would need to
        // support movies + requests space worth of entries.
        fenwick = new FenwickTree(movies + requests);

        // At the same time, we also need to know which positive entry corresponds
        // to which movie title. Hence we need a way to keep track.
        // We will store the index that each movie is located in the index int array.
        index = new int[movies+1];
        for (int i=1; i<=movies; ++i){
            index[i] = movies - i + 1;
        }

        // At the start, all the movies are at the bottom of the stack.
        // Hence the fenwick tree would start off as such.
        for (int i=1; i<=movies; ++i){
            fenwick.update(i, 1);
        }

        // OK that's the preprocessing done. Now for each request
        for (int i=0; i<requests; ++i){
            // Figure out which is the request.
            int req = Integer.parseInt(dlist[i]);

            // Find out how many movies are above it, and store it in output
            // Do this by counting the number of movies below it and subtracting
            // that from the total number of movies.
            output[i] = movies - fenwick.rsq(index[req]);

            // Then set the position of the stack to 0 (by subtracting 1)
            fenwick.update(index[req], -1);

            // And putting the request at the top of the stack.
            // The top of the stack is given by nummovies + i;
            index[req] = movies + i + 1;
            fenwick.update(index[req], 1);
        }

        // Lastly, for all the outputs, print it in a line.
        OutputStream log = new BufferedOutputStream (System.out);
        for (int i=0; i<requests-1; ++i){
            log.write(String.valueOf(output[i]).getBytes());
            log.write(' ');
            log.flush();
        }
        log.write(String.valueOf(output[requests-1]).getBytes());
        log.write('\n');
        log.flush();
    }

    // Main method
    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());
        while (testcases > 0){
            String[] dlist = r.readLine().split(" ");
            MovieCollection movie = new MovieCollection();
            movie.run(Integer.parseInt(dlist[0]), Integer.parseInt(dlist[1]), r);
            testcases--;
        }
    }
}
