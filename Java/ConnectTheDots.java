import java.util.*;
import java.io.*;

public class ConnectTheDots{
    // Helper function to convert a number into an index.
    private static int charToIndex(char a){
        if (a-'9' < 1) return a - '0';
        else if (a-'Z' < 1) return 36 + a - 'A';
        else return 10 + a - 'a';
    }

    // Cast each character into an int
    private static int[] StringToInt(String message) {
        int[] intArray = new int[message.length()];
        for(int i = 0; i < message.length(); i++){
            intArray[i] = message.charAt(i);
        }
        return intArray;
    }

    public static String IntToString (int[] array) {
        StringBuilder builder = new StringBuilder();
        for (int x : array) builder.append((char) x);
        return builder.toString();
    }

    public static void main(String[] args){
        try {
            BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
            // Keep reading the line until we reach EOF (null)
            while (true){
                String line = r.readLine();
                if (line == null) break;

                // Initialise the variables
                int[][] grid = new int[101][101];
                int[][] pos = new int[70][2];
                int numCols = 0;
                int maxIndex = 0;

                // Read the input and push into grid
                // Push position of each non-dot character into pos
                while (line != null && !line.equals("")){
                    for (int i=0; i<line.length(); ++i){
                        if (line.charAt(i) != '.'){
                            int charInd = charToIndex(line.charAt(i));
                            pos[charInd][1] = i;
                            pos[charInd][0] = numCols;
                            maxIndex = Math.max(maxIndex, charInd);
                        }
                    }
                    grid[numCols++] = StringToInt(line);
                    line = r.readLine();
                }

                // For each next to each other character, change the dots
                int step = 0;
                for (int i=0; i<maxIndex; i++){
                    int xpos = pos[i][0];
                    if (xpos == pos[i+1][0]){
                        step = (int) Math.signum(pos[i+1][1]-pos[i][1]);
                        for (int j=pos[i][1]; j != pos[i+1][1]; j+=step){
                            if (grid[xpos][j] == '.') grid[xpos][j] = (int) '-';
                            else if (grid[xpos][j] == '|') grid[xpos][j] = (int)'+';
                        }
                    }
                    else{
                        int ypos = pos[i][1];
                        step = (int) Math.signum(pos[i+1][0]-pos[i][0]);
                        for (int j=pos[i][0]; j != pos[i+1][0]; j+=step){
                            if (grid[j][ypos] == '.') grid[j][ypos] = (int) '|';
                            else if (grid[j][ypos] == '-') grid[j][ypos] = (int)'+';
                        }
                    }
                }
                for (int i=0; i<numCols; i++) System.out.println(IntToString(grid[i]));
                if (line != null) System.out.print("\n");
            }
        }
        catch (IOException e){}
    }
}
