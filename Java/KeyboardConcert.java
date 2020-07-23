import java.io.*;
import java.util.*;

public class KeyboardConcert{
    ArrayList<Set<Integer>> instruments = new ArrayList<>();

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Create my set of instruments
        for (int i = 0; i < n; ++i){
            instruments.add(new HashSet<>());

            dlist = r.readLine().split(" ");
            int k = Integer.parseInt(dlist[0]);

            for (int j = 1; j <= k; ++j){
                instruments.get(i).add(Integer.parseInt(dlist[j]));
            } 
        }

        int out = 0;
        HashSet<Integer> possible = new HashSet<>();

        for (int i = 0; i < n; ++i){
            possible.add(i);
        }

        // Process the stream of notes as it comes. Greedy.
        dlist = r.readLine().split(" ");
        for (int i = 0; i < m; ++i){
            int note = Integer.parseInt(dlist[i]);

            HashSet<Integer> newPossible = new HashSet<>();

            for (int instrument : possible){
                if (instruments.get(instrument).contains(note)){
                    newPossible.add(instrument);
                }
            }

            // Do we not have an instrument that can play the current note?
            // If we don't we have chosen some instrument that got us so far.
            if (newPossible.size() == 0){
                out++;
                for (int a = 0; a < n; ++a){
                    newPossible.add(a);
                }

                // Replay this note, but with a full set of instruments now...
                i--;
            }

            possible = newPossible;
        }

        // If we have not chosen an instrument at the end, we switched for nothing!:
        if (possible.size() == n){
            out--;
        }

        // Stupid edge case: If all instruments can play all notes, then we don't
        // need to out--
        if (out < 0) out = 0;

        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        KeyboardConcert keyboard = new KeyboardConcert();
        keyboard.run();
    }
}

