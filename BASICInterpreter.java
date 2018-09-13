import java.io.*;
import java.util.*;

class Event implements Comparable<Event>{
    int lineNum;
    int eventType;
    String var1;
    String var2;
    int cmpType;
    int goToLine;

    boolean compareTo (Event e){
        return this.lineNum < e.lineNum;
    }

    // Public constructor for goto statements
    public Event(int lineNum, int type, int goToLine){
        this.lineNum = lineNum;
        this.eventType = type;
        this.goToLine = goToLine;
    }

    // Public constructor for 1 var statements, like PRINT/LN
    public Event(int lineNum, int type, String var1){
        this.lineNum = lineNum;
        this.eventType = type;
        this.var1 = var1;
    }

    // Public constructor for 2 var statements, like PRINTLN
    public Event(int lineNum, int type, String var1, String var2){
        this.lineNum = lineNum;
        this.eventType = type;
        this.var1 = var1;
        this.var2 = var2;
    }

    // Public constructor for 1 var 1 int
    public Event(int lineNum, int type, String var1, int var2){
        this.lineNum = lineNum;
        this.eventType = type;
        this.var1 = var1;
        this.goToLine = var2;
    }

    // Public constructor for 3 var statements, like COMPARE
    public Event(int lineNum, int type, String var1, String var2, int cmpType){
        this.lineNum = lineNum;
        this.eventType = type;
        this.var1 = var1;
        this.var2 = var2;
        this.cmpType = cmpType;
    }

    public void process(HashMap globals){
        // This is the let event with a constant.
        if (this.eventType == 0){
            globals.get(this.var1);

        }

        // Let event with another variable.
        if (this.eventType == 1){


        }

        // Let event with an expression
        else if 
    }
}

public class BASICInterpreter{

    // Returns true if input is a number
    // Ripped off StackOverflow
    public static boolean isNumeric(String str){
        return str.matches("-?\\d+(\\.\\d+)?");
    }

    public static void main(String[] args) throws IOException{
        HashMap<String, Integer> globals = new HashMap<>();
        TreeSet<Event> program = new TreeSet<>();
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String str = r.readLine();
        while (str != null){
            // LET statments, gets value 0.
            if (str.equals("LET")){
                String[] dlist = str.split(" ");
                int lineNum = Integer.parseInt(dlist[0]);
                String var = dlist[2];
                // Check to see the number of variables
                if (dlist.length() == 5){
                    if (isNumeric(dlist[3])){
                        program.add(new Event(lineNum, 0, var, Integer.parseInt(dlist[3])));
                    }
                    else {
                        program.add(new Event(lineNum, 1, var, dlist[3]));
                    }
                    continue;
                }

                // There are 2 variables
                boolean 
                if (isNumeric(dlist[3]) && isNumeric(dlist[5]))

            }

            // IF statement


            n = r.readLine();
        }
    }
}
