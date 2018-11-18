import java.io.*;
import java.util.*;

public class Firefly{
    private int min(int x, int y){
        return (x < y) ? (x) : (y);
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");

        // Scan in input
        int n = Integer.parseInt(dlist[0]);
        int H = Integer.parseInt(dlist[1]);

        int[][] heightOfObstacles = new int[H][2];
        int[][] numObstacles = new int[H][2];

        // Read in the input. Rememeber to split them into top and bottoms
        for (int i = 0; i < n; ++i){
            int ph = Integer.parseInt(r.readLine()) - 1;
            heightOfObstacles[ph][i%2]++;
        }

        // Now we loop through all possible heights twice and see how many obstacles
        // we meet. This is done with a very naive prefix sum.
        // Add from the bottom for the stalagmites, and from the top for the stalagtites
        int currTop = 0;
        int currBot = 0;
        for (int i = H; i > 0; --i){
            currTop += heightOfObstacles[i-1][0];
            numObstacles[i-1][0] = currTop;
            currBot += heightOfObstacles[i-1][1];
            numObstacles[H-i][1] = currBot;
        }

        // For every possible height, choose the smallest value:
        int count = 0;
        int out = 9999999;
        for (int i = 0; i < H; ++i){
            int obstacles = numObstacles[i][0] + numObstacles[i][1];
            if (out == obstacles){
                count++;
            }
            else if (out > obstacles){
                out = obstacles;
                count = 1;
            }
        }

        System.out.printf("%d %d\n", out, count);
    }

    public static void main(String[] args) throws IOException{
        Firefly firefly = new Firefly();
        firefly.run();
    }
}
