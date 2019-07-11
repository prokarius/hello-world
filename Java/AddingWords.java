import java.io.*;
import java.util.*;

public class AddingWords{
    HashMap<String, Integer> mapping = new HashMap<>();
    HashMap<Integer, String> revMapping = new HashMap<>();

    private void printEquation(String[] dlist, String result){
        for (int index = 1; index < dlist.length; ++index){
            System.out.printf("%s ", dlist[index]);
        }

        // If result is null, then it's a syntax error
        if (result == null){
            System.out.println("unknown");
            return;
        }

        // Print the result
        System.out.println(result);
    }

    private void processInput(String input){
        // 3 cases: When input is clear, then reset the HashMap
        if (input.equals("clear")){
            mapping.clear();
            revMapping.clear();
            return;
        }

        String[] dlist = input.split(" ");

        // Case 2: If the first word is "def"
        if (dlist[0].equals("def")){
            int integer = Integer.parseInt(dlist[2]);

            // Don't forget to remove the old definition
            revMapping.remove(mapping.get(dlist[1]));

            mapping.put(dlist[1], integer);
            revMapping.put(integer, dlist[1]);
            
            return;
        }

        // Case 3: Calculate the result
        Integer result = mapping.get(dlist[1]);

        // Before checking, check if result is null
        if (result == null){
            printEquation(dlist, null);
            return;
        }

        // Calculate the results 
        int index = 2;
        while (!dlist[index].equals("=")){
            Integer variable = mapping.get(dlist[index + 1]);

            if (variable == null){
                printEquation(dlist, null);
                return;
            }

            // Check for the equations
            if (dlist[index].equals("+")){
                result += variable;
            }
            else { // minus
                result -= variable;
            }

            index += 2;
        }

        printEquation(dlist, revMapping.get(result));
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String line = r.readLine();
        while (line != null){
            processInput(line);
            line = r.readLine();
        }
    }

    public static void main(String[] args) throws IOException{
        AddingWords solution = new AddingWords();
        solution.run();
    }
}
