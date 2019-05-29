import java.io.*;
import java.util.*;

public class PrincessPeach{
    private void run() throws IOException{
        // Treeset to store the input
        TreeSet<Integer> obstacles = new TreeSet<>();

        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        String[] dlist = r.readLine().split(" ");
        int N = Integer.parseInt(dlist[0]);
        int Y = Integer.parseInt(dlist[1]);

        // Add all the obstacles to the treeset
        for (int i = 0; i < Y; ++i){
            int obstacle = Integer.parseInt(r.readLine());
            obstacles.add(obstacle);
        }

        // Loop through all obstacles and see if it's in the list of obstacle
        for (int i = 0; i < N; ++i){
            if (obstacles.contains(i)) continue;
            System.out.println(i);
        }

        System.out.printf("Mario got %d of the dangerous obstacles.\n", obstacles.size());
    }

    public static void main(String[] args) throws IOException{
        // Because she always needs saving XD
        PrincessPeach useless = new PrincessPeach();
        useless.run();
    }
}
