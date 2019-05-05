import java.util.*;
import java.io.*;

public class XOREquation{
    // We need a place to keep all possible permutations
    HashSet<Integer> permuteA = new HashSet<>();
    HashSet<Integer> permuteB = new HashSet<>();
    HashSet<Integer> permuteC = new HashSet<>();

    // Basic recursive way to get all possible permutations 
    private void permute(String input, HashSet<Integer> toPush, int curr, int value){
        // Base case, if the current char is the end of the string, push!
        if (curr == input.length()){
            toPush.add(value);
            return;
        }

        // 2 cases, if the current character is not a "?", multiply by 10
        if (input.charAt(curr) != '?'){
            int digit = input.charAt(curr) - '0';
            permute(input, toPush, curr+1, value*10 + digit);
        }
        
        // Else, enumerate all possible digits
        else {
            int i;

            // BUT IF WE ARE AT THE FIRST DIGIT, START FROM 1!!
            if (curr == 0){
                i = 1;
            }
            else {
                i = 0;
            }

            // Enumerate
            for (; i < 10; ++i){
                permute(input, toPush, curr+1, value*10 + i);
            }
        }
    }
 
    // Recursive check if num can be turned into input
    private boolean possible (int num, String input, int position){
        // Base case, if position = -1, then num == input
        if (position == -1) return true;

        // Prune if num == 0 already
        if (num == 0){
            // But if position != 0 it might be true!
            if (position == 0){
                // But that is only true if input[0] == 0 or '?'
                if (input.charAt(0) == '0' || input.charAt(0) == '?'){
                    return true;
                }
                return false;
            }
            return false;
        }

        // Check if the current digit matches the input
        if (input.charAt(position) == '?'){
            return possible(num/10, input, position-1);
        }
        else if (input.charAt(position) - '0' == num % 10){
            return possible(num/10, input, position-1);
        }
        else {
            return false;
        }
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String[] dlist = r.readLine().split(" ");
        String first = dlist[0];
        String second = dlist[2];
        String third = dlist[4];

        // Yes I know this is really crappy code. Sorry.
        // I wanted to just solve this problem in a way that people can follow.

        // Count the number of '?' in each
        int count1 = 0;
        int count2 = 0;
        int count3 = 0;
        for (int i = 0; i < first.length(); ++i){
            if (first.charAt(i) == '?'){
                count1++;
            }
        }

        for (int i = 0; i < second.length(); ++i){
            if (second.charAt(i) == '?'){
                count2++;
            }
        }

        for (int i = 0; i < third.length(); ++i){
            if (third.charAt(i) == '?'){
                count3++;
            }
        }

        // Find the number with the maximum number of '?'
        int maxQuestion = Math.max(Math.max(count1, count2), count3);
        String a, b, c;
        if (count1 == maxQuestion){
            a = second;
            b = third;
            c = first;
        }
        else if (count2 == maxQuestion){
            a = first;
            b = third;
            c = second;
        }
        else {
            a = second;
            b = first;
            c = third;
        }

        // OK enumerate all possible numbers for a and b
        // DO NOT DO IT FOR C BECAUSE IF THERE IS A LOT OF ?, WILL MLE
        permute(a, permuteA, 0, 0);
        permute(b, permuteB, 0, 0);

        // DUCT TAPE: If either a or b is the single '?', add 0
        if (a.equals("?")){
            permuteA.add(0);
        }
        if (b.equals("?")){
            permuteB.add(0);
        }

        // For all possible values of a and b, if c can match a^b, add 1
        int out = 0;
        int lengthC = c.length()-1;
        for (int i : permuteA){
            for (int j : permuteB){
                // Prune if i^j is not the same length as c
                if (String.valueOf(i^j).length() != c.length()){
                    continue;
                }
                if (possible(i^j, c, lengthC)){
                    out++;
                }
            }
        }

        // Then print it out
        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        XOREquation xor = new XOREquation();
        xor.run();
    }
}
