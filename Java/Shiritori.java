import java.io.*;
import java.util.*;

public class Shiritori{
    private void run() throws IOException{
        HashSet<String> strings = new HashSet<>();

        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        
        String curr = r.readLine();
        strings.add(curr);

        for (int i = 1; i < n; ++i){
            String word = r.readLine();

            // If the person said the word before
            if (strings.contains(word)){
                System.out.printf("Player %d lost\n", i % 2 == 0 ? 1 : 2);
                return;
            }

            // If the last letters don't match
            if (word.charAt(0) != curr.charAt(curr.length()-1)){
                System.out.printf("Player %d lost\n", i % 2 == 0 ? 1 : 2);
                return;
            }

            // Else add the word to the hashset
            strings.add(word);
            curr = word;
        }

        System.out.println("Fair Game");
    }

    public static void main(String[] args) throws IOException{
        Shiritori shiritori = new Shiritori();
        shiritori.run();
    }
}
