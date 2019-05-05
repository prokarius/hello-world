import java.io.*;
import java.util.*;

public class KattissQuest{
    final long ZILLION = 1000000000000L; // 10**12
    final long MILLION = 1000000L;       // 10**6

    // We need a TreeSet to keep track of quests
    // Each quest is represented by E * 10**12 + G * 10**6 + QueryID
    private TreeSet<Long> heapq = new TreeSet<>();

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        // Scan in input
        int q = Integer.parseInt(r.readLine());

        for (int id = 1; id <= q; ++id){
            // Parse each command
            String[] dlist = r.readLine().split(" ");
            if (dlist[0].equals("add")){
                long E = Long.parseLong(dlist[1]);
                long G = Long.parseLong(dlist[2]);
                E *= ZILLION;
                G *= MILLION;

                heapq.add(E + G + id);
            }

            else { // dlist[1] == "query"
                long X = Long.parseLong(dlist[1]);
                long totalGold = 0;

                // Find the largest gold, largest energy that is lower than X+1
                Long highestBidder = heapq.lower((X+1) * ZILLION);
                while (highestBidder != null){
                    heapq.remove(highestBidder);
                    long energy = highestBidder / ZILLION;
                    long gold = (highestBidder / MILLION) % MILLION;
                    X -= energy;
                    totalGold += gold;
                    highestBidder = heapq.lower((X+1) * ZILLION);
                }

                // Print output
                log.write(String.valueOf(totalGold).getBytes());
                log.write('\n');
                log.flush();
            }
        }
    }

    public static void main(String[] args) throws IOException{
        KattissQuest solution = new KattissQuest();
        solution.run();
    }
}
