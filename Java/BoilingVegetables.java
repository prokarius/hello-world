import java.io.*;
import java.util.*;

// Encapsulates a vegetable object
class Vegetable implements Comparable<Vegetable>{
    private double size;
    private int numPieces;

    public Vegetable(double size){
        this.size = size;
        this.numPieces = 1;
    }

    // Overload the constructor so we can make custom vegetables
    public Vegetable(double size, int numPieces){
        this.size = size;
        this.numPieces = numPieces;
    }

    public double getActualSize(){
        return this.size / this.numPieces;
    }

    public double getSize(){
        return this.size;
    }

    public int getNumPieces(){
        return this.numPieces;
    }

    public int compareTo(Vegetable other){
        return (this.getActualSize() > other.getActualSize())?(1):(-1);
    }
}

public class BoilingVegetables{
    TreeSet<Vegetable> vegetables = new TreeSet<>();

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");

        double ratio = Double.parseDouble(dlist[0]);
        int n = Integer.parseInt(dlist[1]);

        dlist = r.readLine().split(" ");
        for (int i = 0; i < n; ++i){
            vegetables.add(new Vegetable(Double.parseDouble(dlist[i])));
        }

        // Now we keep slicing the vegetable as long as the difference in size
        // between the largest and smallest is still larger than the ratio
        int ans = 0;

        while (true){
            Vegetable first = vegetables.first();
            Vegetable last = vegetables.last();

            // Find the ratio between them and break if they are OK
            double currRatio = first.getActualSize() / last.getActualSize();
            if (currRatio > ratio) break;

            // Else split the large vegetable one time!
            vegetables.pollLast();
            vegetables.add(new Vegetable(last.getSize(), last.getNumPieces() + 1));

            ++ans;
        }

        // Print the answer
        System.out.println(ans);
    }

    public static void main(String[] args) throws IOException{
        BoilingVegetables solution = new BoilingVegetables();
        solution.run();
    }
}

