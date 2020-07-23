import java.io.*;
import java.util.*;

class Buyer implements Comparable<Buyer>{
    long demand;
    long price;

    public Buyer(long demand, long price){
        this.demand = demand;
        this.price = price;
    }

    // Lets do this OOP style haha
    public long sell(long weight){
        this.demand--;
        return this.price*weight;
    }

    public boolean want(){
        return (this.demand > 0);
    }

    // Sort by price
    public int compareTo(Buyer other){
        return (this.price > other.price)?1:-1;
    }
}

public class Fishmongers{
    ArrayList<Long> fishies = new ArrayList<>();
    ArrayList<Buyer> buyers = new ArrayList<>();

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        dlist = r.readLine().split(" ");
        for (int i = 0; i < n; ++i){
            fishies.add(Long.parseLong(dlist[i]));
        }

        for (int i = 0; i < m; ++i){
            dlist = r.readLine().split(" ");
            long demand = Long.parseLong(dlist[0]);
            long price = Long.parseLong(dlist[1]);
            buyers.add(new Buyer(demand, price));
        }

        // Sort both arrays
        Collections.sort(fishies, Collections.reverseOrder());
        Collections.sort(buyers, Collections.reverseOrder());

        // Sell your fishies to the best buyer.
        long out = 0;
        int customerNum = 0;

        // OK whatever lets just do try catch because
        try {
            for (Long fish : fishies){
                // Does the customer still want?
                while (!buyers.get(customerNum).want()) customerNum++;
                out += buyers.get(customerNum).sell(fish);
            }
        }
        catch (Exception e) {}

        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        Fishmongers fishmonger = new Fishmongers();
        fishmonger.run();
    }
}

