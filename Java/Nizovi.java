import java.util.*;

public class Nizovi{
    public static void ind(int indent){
        for (int j=0; j<indent; ++j){
            System.out.printf(" ");
        }
    }


    public static void main(String[] args){
        Scanner s = new Scanner(System.in);
        String in = s.next();
        char[] line = in.toCharArray();
        int indent = 0;
        int i = 0;
        while (i < in.length()){
            // If it's a open, print a "{", a new line, and increase indent
            if (line[i] == '{'){
                indent += 2;
                System.out.println("{");

                // Check the next guy
                // If it is a close, then just print it
                // Note that it is not possible for the last char to be a close.
                // So this will not AIOOB or NPE
                if (line[i+1] == '}'){
                    i++;
                    indent -= 2;
                    ind(indent);
                    System.out.printf("}");
                }
                else{
                    ind(indent);
                }
            }
            else if (line[i] == '}'){
                System.out.printf("\n");
                indent -= 2;
                ind(indent);
                System.out.printf("}");
            }
            // If it's a comma, just print it and a new line
            else if (line[i] == ','){
                System.out.println(",");
                ind(indent);
            }
            // Else it's just a character. Print it
            else {
                System.out.printf("%c", line[i]);
            }
            i++;
        }
        System.out.printf("\n");
    }
}
