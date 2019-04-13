import java.io.*;
import java.util.*;

public class AbandonedAnimal{
    private void run() throws IOException{ 
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        ArrayList<String> ingredients = new ArrayList<>();
        HashMap<Integer, HashSet<String>> inventory = new HashMap<>();

        int N = Integer.parseInt(r.readLine());
        int K = Integer.parseInt(r.readLine());
        
        // For each store:
        for (int i = 0; i < K; ++i){
            String[] dlist = r.readLine().split(" ");
            int store = Integer.parseInt(dlist[0]);
        
            // Populate the stores inventory
            if (!inventory.containsKey(store)){
                inventory.put(store, new HashSet<>());
            }
            inventory.get(store).add(dlist[1]);
        }

        // Scan in the ingredients list
        int M = Integer.parseInt(r.readLine());

        for (int i = 0; i < M; ++i){
            ingredients.add(r.readLine());
        }

        // For each ingredient, go through the list of stores front to end.
        // Greedily choose the ingredients from the stores if you can.
        ArrayList<Integer> sequence = new ArrayList<>();
        int currentStore = 0;
        int currentItem = 0;
        while (currentItem < M){
            if (currentStore >= N) break;
            while (currentStore < N){
                if (!inventory.containsKey(currentStore)){
                    currentStore++;
                    continue;
                }
                if (inventory.get(currentStore).contains(ingredients.get(currentItem))){
                    sequence.add(currentStore);
                    currentItem++;
                    break;
                }
                else {
                    currentStore++;
                }
            }
        }

        
        // If we have not reached the end of the ingredients list, it's impossible
        if (currentItem != M){
            System.out.println("impossible");
            return;
        }

        // Now to see if the list is unique, go from the back to see if you get the
        // same sequence
        // CurrentItem is already at M, so just minus 1 and continue
        currentItem--;
        currentStore = N-1;
        while (currentItem >= 0){
            if (currentStore < 0) break;
            while (currentStore >= 0){
                if (!inventory.containsKey(currentStore)){
                    currentStore--;
                    continue;
                }
                if (inventory.get(currentStore).contains(ingredients.get(currentItem))){
                    // If the store number is not the same, print ambiguous and break
                    if (sequence.get(currentItem) != currentStore){
                        System.out.println("ambiguous");
                        return;
                    }
                    currentItem--;
                    break;
                }
                else {
                    currentStore--;
                }
            }
        }

        // If we are here, we have no more items to go through
        System.out.println("unique");
    }

    public static void main(String[] args) throws IOException{
        AbandonedAnimal animal = new AbandonedAnimal();
        animal.run();
    }
}
