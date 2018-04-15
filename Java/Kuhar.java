import java.util.*;
import java.io.*;

// Encapsulates the idea behind the Ingredients
class Ingredient{
    private int needed;
    private int have;
    private int smallprice;
    private int largeprice;
    private int smallamount;
    private int largeamount;

    // Public constructor. Essentially it saves all the stuff
    public Ingredient(int needed, int have, int smallprice, int largeprice,
                      int smallamount, int largeamount){
        this.needed = needed;
        this.have = have;
        this.smallprice = smallprice;
        this.largeprice = largeprice;
        this.smallamount = smallamount;
        this.largeamount = largeamount;
    }

    // Returns the cost of having to get n of said ingredients
    // Iteratively steps through each possible number of large bag
    public int getCost(int n){
        // Check if we even need to buy anything at all
        if (n < 1){
            return 0;
        }

        // Initialise best to when we can buy using all large bags
        int best = ((n + largeamount - 1)/largeamount)*largeprice;
        int res;
        int numlarge = 0;

        // Then slowly step through all possible numbers of large bags
        // This will go until the number of ingredients we have to buy is negative
        while (n >= 0){
            int numsmall = (n + smallamount - 1)/smallamount;
            res = numlarge*largeprice + numsmall*smallprice;
            best = (best < res) ? (best) : (res);
            numlarge++;
            n -= largeamount;
        }
        return best;
    }

    // Given a number of meals n, returns the number of extra ingredients needed
    // to make it.
    public int getNumNeeded (int n){
        return n*this.needed - this.have;
    }
}

public class Kuhar{
    ArrayList<Ingredient> ingredients = new ArrayList<>();
    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] nandk = r.readLine().split(" ");
        int n = Integer.parseInt(nandk[0]);
        int k = Integer.parseInt(nandk[1]);

        // For each ingredient, add it to the ingredient list.
        for (int i=0; i<n; ++i){
            String[] dlist = r.readLine().split(" ");
            ingredients.add(new Ingredient(
                            Integer.parseInt(dlist[0]), Integer.parseInt(dlist[1]),
                            Integer.parseInt(dlist[3]), Integer.parseInt(dlist[5]),
                            Integer.parseInt(dlist[2]), Integer.parseInt(dlist[4])));
        }

        // Do a binary search and print the result
        System.out.println(binarySearch(k));
    }

    // Irham's Binary Search Template
    private int binarySearch(int money){
        int left = 0;
        int right = 1<<20;
        int best = -1;
        while (left <= right){
            int mid = left + (right - left)/2;
            if (check(mid, money)){
                best = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return best;
    }

    // Given an integer n and some amount of money
    // Return true if it's possible to prepare n meals with the amount of money
    private boolean check(int n, int money){
        for (Ingredient i : ingredients){
            int needed = i.getNumNeeded(n);
            money -= i.getCost(needed);

            // If we ever run out of money in the middle, just return false.
            if (money < 0){
                return false;
            }
        }

        // If we made it to the end with some money left, yay. Return true.
        return true;
    }

    public static void main(String[] args) throws IOException{
        Kuhar kuhar = new Kuhar();
        kuhar.run();
    }
}
