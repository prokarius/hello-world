import java.io.*;
import java.util.*; 

public class XorMaximization{
    private HashSet<Long>[] gaussJordan = new HashSet[64];
    private ArrayList<Long> output = new ArrayList<>();

    private int getMsb(long num){
        return 63 - Long.numberOfLeadingZeros(num);
    }

    private void run() throws IOException{
        // Set up
        for (int i = 0; i < 64; ++i){
            gaussJordan[i] = new HashSet<>();
        }

        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        String[] dlist = r.readLine().split(" ");
        for (String str : dlist){
            long x = Long.parseLong(str);
            gaussJordan[getMsb(x)].add(x);
        }

        // Do Gaussian Elimination
        for (int msb = 63; msb >= 0; --msb){
            if (gaussJordan[msb].size() == 0) continue;

            long basisVector = gaussJordan[msb].stream().findFirst().get();
            output.add(basisVector);
            for (long x : gaussJordan[msb]) {
                long newElem = x ^ basisVector;
                if (newElem == 0) continue;
                gaussJordan[getMsb(newElem)].add(newElem);
            }
        }

        // DP
        long best = 0;
        for (long basisVector : output){
            long newBest = best ^ basisVector;
            best = (newBest > best)?(newBest):(best);
        }
        System.out.println(best);
    }

    public static void main(String[] args) throws IOException{
        XorMaximization xor = new XorMaximization();
        xor.run();
    }
}

