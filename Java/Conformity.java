import java.util.*;

public class Conformity{
    private static ArrayList<Long> in = new ArrayList<>(); // Saves the input
    private static HashMap<Long, Integer> choiceSet = new HashMap<>(); // Counts the choices
    private static int max = 0;
    private static int ans = 0;
    public static void main(String[] args){
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        for (int i=0; i<n; ++i){
            int[] choice = new int[5];
            // populate the frosh's choice.
            for (int j=0; j<5; ++j){
                choice[j] = s.nextInt();
            }
            Arrays.sort(choice);

            long out = 0;
            for (int j : choice){
                out = out * 1000 + j;
            }
            in.add(out);
        }

        // For each TreeSet, increment the count by 1.
        for (long tree : in){
            if (choiceSet.containsKey(tree)){
                choiceSet.put(tree, 1 + choiceSet.get(tree));
            }
            else {
                choiceSet.put(tree, 1);
            }
            max = (max > choiceSet.get(tree) ? max : choiceSet.get(tree));
        }


        // Check to see if the treeset is the most popular
        for (long tree: in){
            if (choiceSet.get(tree) == max){
                ans++;
            }
        }

        // Print the answer
        System.out.println(ans);
    }
}
