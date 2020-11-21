import java.io.*;
import java.util.*;

class Tree {
    int count;  // Number of words that started with this number
    HashMap<Character, Tree> childs;

    public Tree (){
        childs = new HashMap<>();
        count = 0;
    }
}

public class BingItOn{
    Tree root = new Tree();

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out);

        int n = Integer.parseInt(r.readLine());

        for (int i = 0; i < n; ++i){
            String word = r.readLine();

            // Insert into the tree
            Tree curr = root;
            int count = 0;

            for (int j = 0; j < word.length(); ++j){
                char letter = word.charAt(j);

                // Have we seen this letter before?
                if (!curr.childs.containsKey(letter)){
                    curr.childs.put(letter, new Tree());
                }

                // Go into the tree
                curr = curr.childs.get(letter);
                curr.count++;
            }

            // Lastly write the output
            log.write(String.valueOf(curr.count-1).getBytes());
            log.write('\n');
        }

        log.flush();
    }

    public static void main(String[] args) throws IOException{
        BingItOn bing = new BingItOn();
        bing.run();
    }
}

