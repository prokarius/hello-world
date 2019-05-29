import java.io.*;
import java.util.*;

class Coordinate{
    private int x;
    private int y;

    public Coordinate(int x, int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return this.x;
    }

    public int getY(){
        return this.y;
    }

    @Override
    public boolean equals(Object other){
        if (other == this) return true;
        if (!(other instanceof Coordinate)) return false;
        Coordinate coordOther = (Coordinate) other;
        return ((this.x == coordOther.x) && (this.y == coordOther.y));
    }

    @Override
    public int hashCode(){
        return -this.x ^ this.y;
    }
}

public class GreetingCard{
    HashSet<Coordinate> coordinates = new HashSet<>();
    ArrayList<Coordinate> coordList = new ArrayList<>();
    int out = 0;

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        
        // Scan in input
        int n = Integer.parseInt(r.readLine());

        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);

            coordinates.add(new Coordinate(x, y));
            coordList.add(new Coordinate(x, y));
        }

        // 2 cases, we'll make the 2 DR arrays here
        int[] dr1 = {0, 2018, 0, -2018, 0};
        int[] dr2 = {1118, 1680, -1118, -1680, 1118, -1680, -1118, 1680, 1118};

        // For each coordinate, BRUTE FORCE
        for (Coordinate coord : coordinates){
            int x = coord.getX();
            int y = coord.getY();

            // Case 1: Delta = (2018, 0)
            for (int k = 0; k < 4; ++k){
                int newx = x + dr1[k];
                int newy = y + dr1[k+1];

                if (coordinates.contains(new Coordinate(newx, newy))) out++;
            }

            // Case 2: Delta = (1118, 1680)
            for (int k = 0; k < 8; ++k){
                int newx = x + dr2[k];
                int newy = y + dr2[k+1];

                if (coordinates.contains(new Coordinate(newx, newy))) out++;
            }
        }

        // At the end just divide by 2
        System.out.println(out/2);
    }

    public static void main(String[] args) throws IOException{
        GreetingCard solution = new GreetingCard();
        solution.run();
    }
}
