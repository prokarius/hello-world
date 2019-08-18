import java.io.*;
import java.util.*;

public class LemonadeTrade{
    HashMap<String, Double> dp = new HashMap<>();
    private double run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // We also have 1L of pink lemonade, which is effectively 0
        dp.put("pink", 0.0);

        // We will process this line by line.
        int n = Integer.parseInt(r.readLine());

        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");

            // Try trading if we have what they want
            if (!dp.containsKey(dlist[1])) continue;

            // Use log because of precision issues and shit
            double amount = dp.get(dlist[1]) + Math.log(Double.parseDouble(dlist[2]));

            // dp[string] stores the max amount of that colour lemonade we can get
            if (!dp.containsKey(dlist[0])){
                dp.put(dlist[0], amount);
            }
            else if (dp.get(dlist[0]) < amount){
                dp.put(dlist[0], amount);
            }
        }

        // Check how much blue lemonade we have
        if (!dp.containsKey("blue")) return 0;
        double blueLemonade = Math.exp(dp.get("blue"));
        if (blueLemonade > 10) return 10;
        return blueLemonade;
    }

    public static void main(String[] args) throws IOException{
        LemonadeTrade lemonade = new LemonadeTrade();
        System.out.println(lemonade.run());
    }
}

