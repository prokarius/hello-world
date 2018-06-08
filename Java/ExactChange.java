import java.util.*;
import java.io.*;

public class ExactChange{
    private void run(BufferedReader r) throws IOException{
        HashSet<Integer> hashset = new HashSet<>();
        HashSet<Integer> temp = new HashSet<>();
        hashset.add(0);

        // Scan in input
        int price = 1000*Integer.parseInt(r.readLine());
        int max = 20000000;
        int numitems = Integer.parseInt(r.readLine());

        // For each item we scan in, add it to each old item
        for (int i=0; i<numitems; ++i){
            int item = 1000*Integer.parseInt(r.readLine());
            for (int oldcost : hashset){

                // If we can use this to pay for the item, that's good.
                // Also check if we pay less than what we used to pay
                int newcost = oldcost + item + 1;
                if (newcost > price){
                    if (newcost < max){
                        max = newcost;
                    }
                }
                else{ // newcost < price
                    temp.add(newcost);
                }
            }

            // Then transfer them back into our original hashset
            for (int newitem : temp){
                hashset.add(newitem);
            }
        }

        // Now max would be the best
        System.out.printf("%d %d\n", max/1000, max%1000);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        ExactChange solution = new ExactChange();
        int testcases = Integer.parseInt(r.readLine());
        while (testcases > 0){
            solution.run(r);
            testcases--;
        }
    }
}
