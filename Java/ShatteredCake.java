import java.util.*;

public class ShatteredCake{
    public void run(){
        Scanner s = new Scanner(System.in);
        int cakeWidth = s.nextInt();
        int numPieces = s.nextInt();

        // Initilise totalArea to be 0
        int totalArea = 0;

        // For each piece, sum up their areas.
        for (int i = 0; i < numPieces; ++i){
            int pieceWidth = s.nextInt();
            int pieceHeight = s.nextInt();
            totalArea += pieceHeight * pieceWidth;
        }

        // Divide by the cakeWidth
        System.out.println(totalArea / cakeWidth);
    }

    public static void main(String[] args){
        ShatteredCake solution = new ShatteredCake();
        solution.run();

    }
}
