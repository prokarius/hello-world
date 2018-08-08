import java.io.*;
import java.util.*;

class Drink{
    String name;
    int units;
    int cost;

    // Public constructor. Does all the shitty parsing
    public Drink(String name, String percent, String size, String cost){
        this.name = name;
        this.cost = (int)(Double.parseDouble(cost) * 100 + 0.5);
        this.units = Integer.parseInt(percent) * 10;
        if (size.charAt(2) == '1'){
            this.units *= 6;
        }
        else if (size.charAt(2) == '2'){
            this.units *= 3;
        }
        else if (size.charAt(2) == '3'){
            this.units *= 2;
        }
    }

    // Getter methods. Because.
    public int getCost(){
        return this.cost;
    }

    public int getPoison(){
        return this.units;
    }

    public String getName(){
        return this.name;
    }
}

class DPState{
    private int numDrinks;
    private int[] drinksArray;
    private boolean state = false;

    public DPState(int numDrinks){
        this.numDrinks = numDrinks;
        this.drinksArray = new int[numDrinks];
    }

    // Shitty solution. But it shouldn't TLE cuz the numbers are small
    // I should never do this. Please think through your code properly next time.
    // Proper way is to simply update the array instead of copying the whole thing.
    public void update(int[] drinksArray){
        for (int i = 0; i < this.numDrinks; ++i){
            this.drinksArray[i] = drinksArray[i];
        }
        this.state = true;
    }

    // Even shittier bit: Initialising the start state of the dp should not be
    // a method. I have no idea what Im doing at this point. Whatever works I guess.
    public void init(){
        for (int i = 0; i < this.numDrinks; ++i){
            this.drinksArray[i] = 0;
        }
        this.state = true;
    }

    public int[] getDrinks(){
        return this.drinksArray;
    }

    public boolean getState(){
        return this.state;
    }
}

public class DrinkResponsibly{
    public void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");

        // Since the smallest denom of a drink is 1/3L at 1%, that is 0.33 units
        // But the amount of alcohol is a 1 dp number.
        // Also, note that 1/2L of a drink at 1% is 0.5 units
        // This means if the dp is not 0 or 5, then screw it, it's never gonna work.
        int alcohol = (int)(Double.parseDouble(dlist[1]) * 10 + 0.5);
        alcohol *= 6;

        // Parse the strings into integers
        // Alcohol amount is expressed as the number of 1/6s of a unit.
        int money = (int)(Double.parseDouble(dlist[0])*100 + 0.5);
        int n = Integer.parseInt(dlist[2]);

        // Initialise dp states
        int numstates = (alcohol+1)*(money+1);
        DPState[] dp = new DPState[numstates];
        for (int i = 0; i < numstates; ++i){
            dp[i] = new DPState(n);
        }
        dp[0].init();

        // Also store the drinks because Im stupid there is no need to what am I doing
        Drink[] drinks = new Drink[n];

        // For each drink, update the dp state
        for (int i = 0; i < n; ++i){
            String[] dlist2 = r.readLine().split(" ");
            Drink drink = new Drink(dlist2[0], dlist2[1], dlist2[2], dlist2[3]);
            drinks[i] = drink;

            // For each cost price to reach the top
            for (int j = 0; j <= money - drink.getCost(); ++j){
                // For each toxicity of the drink
                for (int k = 0; k <= alcohol - drink.getPoison(); ++k){
                    int currstate = j*(alcohol+1) + k;

                    // If we have reached this state before, pump it forwards.
                    if (dp[currstate].getState()){
                        int nextstate = (j + drink.getCost())*(alcohol+1) + (k + drink.getPoison());
                        if (!dp[nextstate].getState()){
                            int[] drinksarray = dp[currstate].getDrinks().clone();
                            drinksarray[i]++;
                            dp[nextstate].update(drinksarray);
                        }
                    }
                }
            }
        }

        // Now we check the dp state
        if (!dp[numstates-1].getState()){
            System.out.println("IMPOSSIBLE");
            return;
        }
        int[] output = dp[numstates-1].getDrinks();
        for (int i = 0; i < n; ++i){
            if (output[i] != 0){
                System.out.printf("%s %d\n", drinks[i].getName(), output[i]);
            }
        }
    }

    public static void main(String[] args) throws IOException{
        DrinkResponsibly solution = new DrinkResponsibly();
        solution.run();
    }
}
