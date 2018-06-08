import java.io.*;
import java.util.*;

public class Arbitrage{
    HashMap<String, Integer> hashmap = new HashMap<>();
    double[][] adjmatrix;

    private void run(int c, BufferedReader r) throws IOException{
        // Scan in the list of currencies
        String[] currlist = r.readLine().split(" ");
        for (int i = 0; i < c; ++i){
            hashmap.put(currlist[i], i);
        }

        // Setup my adjmatrix and initial floyd to infinity.
        adjmatrix = new double[c][c];
        for (int i = 0; i < c; ++i){
            for (int j = 0; j < c; ++j){
                adjmatrix[i][j] = 2000000000;
            }
        }

        for (int i = 0; i < c; ++i){
            adjmatrix[i][i] = 0;
        }

        // Scan in the list of currencies.
        int rows = Integer.parseInt(r.readLine());
        for (int i = 0; i < rows; ++i){
            String[] dlist = r.readLine().split(" ");
            int start = hashmap.get(dlist[0]);
            int end = hashmap.get(dlist[1]);
            String[] dlist2 = dlist[2].split(":");
            double weight = Math.log10(Double.parseDouble(dlist2[0])/Double.parseDouble(dlist2[1]));
            adjmatrix[start][end] = weight;
        }

        // Do Floyd Warshall's.
        boolean arbitrage = false;
        for (int i = 0; i < c; ++i){
            for (int j = 0; j < c; ++j){
                for (int k = 0; k < c; ++k){
                    if (adjmatrix[i][j] > adjmatrix[i][k] + adjmatrix[k][j]){
                        adjmatrix[i][j] = adjmatrix[i][k] + adjmatrix[k][j];
                    }
                }
            }

            // Check for a negative cycle by seeing if any diagonals are negative
            // But since we are using doubles, there could be floating point errors
            // Why -1e-7? Idk... I just try my best.
            for (int j = 0; j < c; ++j){
                if (adjmatrix[j][j] < -1e-7){
                    arbitrage = true;
                    break;
                }
            }
        }

        // Print that shit
        System.out.println(arbitrage ? "Arbitrage" : "Ok");
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        int num = Integer.parseInt(r.readLine());
        while (num != 0){
            Arbitrage arbitrage = new Arbitrage();
            arbitrage.run(num, r);
            num = Integer.parseInt(r.readLine());
        }
    }
}

