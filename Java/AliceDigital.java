import java.util.*;
import java.io.*;

// Greedy. Keep a record what the max is
public class AliceDigital{
    public static void main(String[] args){
        try {
            BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
            // Scanner solution in comments
            // Scanner s = new Scanner(System.in);
            int T = Integer.parseInt(r.readLine()); // int T = s.nextInt();
            while (T > 0){
                int curr1 = 0;
                int curr2 = 0;
                int ans = 0;
                int last = 1;
                String[] nAndM = r.readLine().split(" ");
                int n = Integer.parseInt(nAndM[0]); // s.nextInt();
                int m = Integer.parseInt(nAndM[1]); // s.nextInt();

                String[] phArray = r.readLine().split(" ");
                while (n > 0){
                    int ph = Integer.parseInt(phArray[n-1]); // s.nextInt();
                    if (ph > m) curr2 += ph;
                    else{
                        if (last == 0) ans = Math.max(ans, curr2 + curr1 + m);
                        last = (ph == m ? 0 : 1);
                        curr1 = curr2;
                        curr2 = 0;
                    }
                    --n;
                }
                ans = Math.max(ans, curr2 + curr1 + m);
                System.out.printf("%d\n", ans);
                --T;
            }
        }
        catch (IOException e) {}
    }
}
