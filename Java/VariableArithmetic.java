import java.io.*;
import java.util.*;

public class VariableArithmetic{
    HashMap<String, Integer> mapping = new HashMap<>();

    private boolean isAlpha(char firstChar){
        return firstChar >= 'a' && firstChar <= 'z';
    }

    private void processInput(String input){
        String[] dlist = input.split(" ");

        // Not too sure if this will always be defined, but oh well
        // 2 cases, if there is an equal sign, that is an assignment
        if (dlist.length > 1 && dlist[1].equals("=")){
            mapping.put(dlist[0], Integer.parseInt(dlist[2]));
            return;
        }

        // Calculate shit
        ArrayList<String> variables = new ArrayList<>();
        int output = 0;

        // For each variable check if it is a number or not
        for (int i = 0; i < dlist.length; i += 2){
            if (isAlpha(dlist[i].charAt(0))){
                // See if the 
                if (mapping.containsKey(dlist[i])){
                    output += mapping.get(dlist[i]);
                }
                else {
                    variables.add(dlist[i]);
                }
            }
            else { // We have a number
                output += Integer.parseInt(dlist[i]);
            }
        }

        // Remember if the result is non-zero, don't print it
        if (output != 0){
            System.out.printf("%d", output);
            if (variables.size() > 0){
                System.out.printf(" + ");
            }
        }

        for (int i = 0; i < variables.size(); ++i){
            System.out.printf("%s", variables.get(i));
            if (i != variables.size()-1){
                System.out.printf(" + ");
            }
        }

        System.out.println("");
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String line = r.readLine();
        while (!line.equals("0")){
            processInput(line);
            line = r.readLine();
        }
    }

    public static void main(String[] args) throws IOException{
        VariableArithmetic solution = new VariableArithmetic();
        solution.run();
    }
}
