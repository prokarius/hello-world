import java.util.*;
import java.io.*;

public class TheTrip{
    public void run(int n, BufferedReader r) throws IOException{
        System.out.println(n);
        int[] array = new int[n];
        int total = 0;

        // Figure out what is the average amount of money that has been paid.
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split("\\.");
            array[i] = Integer.parseInt(dlist[0]) * 100 + Integer.parseInt(dlist[1]);
            total += array[i];
        }

        int average = total / n;
        int balance = total % n;

        // These will be the statistics.
        int numOver = 0;
        int totalOver = 0;

        // Calculate the total amount that needs to change hands
        for (int i = 0; i < n; ++i){
            if (array[i] > average){
                numOver++;
                totalOver += array[i] - average;
            }
        }

        // Now we want to give the undivided cents (balance) to the people who
        // overpaid (numOver). We try to give as many of the balance to the people
        // who overpaid as possible.
        int out;
        if (numOver >= balance){
            // There are more people who overpaid. From the total amount to
            // transact, we just need to remove the number of cents left over.
            // That will account for the people who over paid.
            out = totalOver - balance;
        }
        else {
            // If not, then we just subtract the number of people who over paid form
            // the balance itself.
            out = totalOver - numOver;
        }

        // Print the answer
        System.out.printf("$%.2f\n", ((double)out)/100);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        while (n != 0){
            new TheTrip().run(n, r);
            n = Integer.parseInt(r.readLine());
        }
    }
}

