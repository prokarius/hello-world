import java.io.*;
import java.util.*;

public class CandyDivision{
    public static void main(String[] args) throws IOException{
        // Initialize our 2 arraylists
        LinkedList<Long> smallDivisors = new LinkedList<>();
        LinkedList<Long> bigDivisors = new LinkedList<>();

        // This is for fast output
        OutputStream log = new BufferedOutputStream (System.out);

        // Read in the number
        Scanner s = new Scanner(System.in);
        long n = s.nextLong();

        // We initialise our divisor variable outside the loop
        // so that we can call it again later.
        long i;

        // We bruteforce each divisor until the square root of the number
        // If it is divisible, we can just push it into both arrays
        for (i = 1; i*i < n; ++i){
            if (n % i == 0){
                smallDivisors.addLast(i);
                bigDivisors.addFirst(n/i);
            }
        }

        // Check for square root case.
        if (n / i == i){
            smallDivisors.addLast(i);
        }

        // We are going to cheat a bit
        // We will remove the 0 because it is the trivial divisor
        log.write('0');
        smallDivisors.pollFirst();

        // For each character, we print the space, then the divisor itself
        for (long divisor : smallDivisors){
            log.write(' ');
            log.write(String.valueOf(divisor - 1).getBytes());
        }

        for (long divisor : bigDivisors){
            log.write(' ');
            log.write(String.valueOf(divisor - 1).getBytes());
        }

        // Flush the OutputStream!
        log.write('\n');
        log.flush();
    }
}


