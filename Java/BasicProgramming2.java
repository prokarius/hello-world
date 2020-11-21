import java.io.*;
import java.util.*;

public class BasicProgramming2{

    int n;
    int[] array;

    private void sum7777(){
        HashSet<Integer> hash = new HashSet<>();

        // For each number, look for its partner
        for (int i : array){
            hash.add(i);

            int partner = 7777 - i;
            if (hash.contains(partner)){
                System.out.println("Yes");
                return;
            }
        }

        // Oh bummer, we didn't find any partners
        System.out.println("No");
        return;
    }

    private void unique(){
        HashSet<Integer> hash = new HashSet<>();

        // Check if the thing already exists in the hash. 
        for (int i : array){
            if (hash.contains(i)){
                System.out.println("Contains duplicate");
                return;
            }
            hash.add(i);
        }

        System.out.println("Unique");
        return;
    }

    private void majority(){
        HashMap<Integer, Integer> count = new HashMap<>();

        // Populate the Hashmap
        for (int i : array){
            if (!count.containsKey(i)){
                count.put(i, 0);
            }
            count.put(i, count.get(i) + 1);
        }

        // Loop through all the items
        for (int i : count.keySet()){
            if (count.get(i) > n/2){
                System.out.println(i);
                return;
            }
        }

        System.out.println("-1");
        return;
    }

    // Bro, you didn't say it needs to be sorted >: (
    private void median(){
        // Sort the array, and output the median(s)
        Arrays.sort(array);

        // If it is odd, just print the dude
        if (n % 2 == 1){
            System.out.printf("%d\n", array[n/2]);
        }

        // If it is even, print both the dudes
        if (n % 2 == 0){
            System.out.printf("%d %d\n", array[n/2 - 1], array[n/2]);
        }
        return;
    }

    private void printHundreds() throws IOException{
        // Sort the array, and loop!
        Arrays.sort(array);

        // Ugh, I forgot java is slow for IO...
        OutputStream log = new BufferedOutputStream (System.out);

        for (int i : array){
            if (i < 1000 && i > 99){
                log.write(String.valueOf(i).getBytes());
                log.write(' ');
            }
        }

        log.write('\n');
        log.flush();
        return;
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        n = Integer.parseInt(dlist[0]);
        int t = Integer.parseInt(dlist[1]);

        array = new int[n];
        dlist = r.readLine().split(" ");
        for (int i = 0; i < n; ++i){
            array[i] = Integer.parseInt(dlist[i]);
        }

        switch (t){
            case (1):
                sum7777();
                return;
            case (2):
                unique();
                return;
            case (3):
                majority();
                return;
            case (4):
                median();
                return;
            case (5):
                printHundreds();
                return;
        }
    }

    public static void main(String[] args) throws IOException{ 
        BasicProgramming2 basic = new BasicProgramming2();
        basic.run();
    }
}

