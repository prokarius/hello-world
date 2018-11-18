import java.io.*;
import java.util.*;

// Encapsulates a LET statement in the program.
class LetEvent extends Event{
    char variable; // The variable we are letting the value.
    char args1;    // The first arguement of the arithmetic statement.
    char args2;    // The (optional) second argument of the arithmetic statement.
    int argsInt1;  // The (constant) integer value of the first argument.
    int argsInt2;  // The (constant, optional) integer value of the second argument.
    boolean isVariable1 = true;   // Stores if the first argument is a variable.
    boolean isVariable2 = true;   // Stores if the second argument is a variable.
    boolean isBifunction = false; // Stores if the arithmetic statement takes 2 arguments.
    int opType;    // Stores the operator type. (Whether it's PLUS MINUS TIMES DIVIDE).

    // Public constructor
    public LetEvent(String string){

        // Start by splitting the input string and setting the varible to be
        // modified and the first argument of the arithmetic statement.
        String[] input = string.split(" ");
        variable = input[0].charAt(0);
        args1 = input[2].charAt(0);

        // If we have more than 3 parts, it means the input arithmetic statement
        // takes in 2 arguments. We then have to set the 2nd argument and the opType.
        if (input.length > 3){
            isBifunction = true;
            args2 = input[4].charAt(0);
            switch (input[3]){
                case "+":
                    opType = 0;
                    break;
                case "-":
                    opType = 1;
                    break;
                case "*":
                    opType = 2;
                    break;
                case "/":
                    opType = 3;
            }
        }

        // Now, for both arguments, we need to check if they are numbers.
        // If the first character is not within the A-Z ascii range, then we can
        // conclude that we are dealing with numbers.
        if (args1 - 'A' < 0){
            isVariable1 = false;
            argsInt1 = Integer.parseInt(input[2]);
        }

        // Do the same for the second argument, but only if arithmetic statement
        // takes in two arguments.
        if (isBifunction){
            if (input[4].charAt(0) - 'A' < 0){
                isVariable2 = false;
                argsInt2 = Integer.parseInt(input[4]);
            }
        }
    }

    @Override
    public void execute(Model model){
        int x, y;

        // Set the variables. If we already know that the inputs to the conditional
        // are going to be non-numeric, we can simply pull out the values.
        if (isVariable1){
            x = model.getVar(args1);
        }
        else {
            x = argsInt1;
        }

        // Of course, in this case, we need to check if the arithmetic statement
        // has more than 1 variable. If it is, then we need to process the let
        // statement seperately.
        if (isBifunction){
            if (isVariable2){
                y = model.getVar(args2);
            }
            else {
                y = argsInt2;
            }

            // Check to see which operator was used in the input, and apply it to
            // the two variables in question.
            switch (opType){
                case 0:
                    model.setVar(variable, x+y);
                    break;
                case 1:
                    model.setVar(variable, x-y);
                    break;
                case 2:
                    model.setVar(variable, x*y);
                    break;
                case 3:
                    model.setVar(variable, x/y);
                    break;
            }
        }

        // If it's one argument, just set the variable to the value.
        else {
            model.setVar(variable, x);
        }

        // Don't forget to advance the PC.
        model.setNextPC();
    }
}

// Encapsulates a PRINT or a PRINTLN statement in the program.
class PrintEvent extends Event{
    String toPrint;      // The string to print.
    char variable;       // Optionally the variable we are supposed to print.
    boolean isVariable;  // If the value to print is a variable.
    boolean isPrintln;   // Whether or not we should print a new line.

    public PrintEvent(String input, boolean type){
        this.isPrintln = type;
        String print = input;

        // If the first character of the input is a " mark:
        if (print.charAt(0) == '"'){
            // Then this is a string!
            isVariable = false;
            toPrint = print.substring(1, print.length() - 1);
        }

        // If not, it is a variable.
        else {
            isVariable = true;
            variable = print.charAt(0);
        }
    }

    @Override
    public void execute(Model model){

        // If it's a variable, get it's value and print it out.
        if (isVariable){
            System.out.printf("%d", model.getVar(variable));
        }

        // If not, print out the string.
        else {
            System.out.printf("%s", toPrint);
        }

        // If it was a println statement, then we print the new line.
        if (isPrintln){
            System.out.printf("\n");
        }

        // Don't forget to set the next PC.
        model.setNextPC();
    }
}

class IfEvent extends Event {
    int gotoLine; // The line number that we have to goto should the condition hold true.
    char args1;   // The first argument of the conditional.
    char args2;   // The second argument of the conditional.
    int argsInt1; // The (constant) integer value of the first argument of the conditional.
    int argsInt2; // The (constant) integer value of the second argument of the conditional.
    boolean isVariable1 = true;   // Stores if the first argument is a variable.
    boolean isVariable2 = true;   // Stores if the second argument is a variable.
    int opType;   // Stores the operator type that is to be used in the conditional.

    public IfEvent (String string){
        // Get the input arguments from the input string.
        String[] input = string.split(" ");
        args1 = input[0].charAt(0);
        args2 = input[2].charAt(0);

        // Set the operator type to be the correct thing.
        switch (input[1]){
            case "=":
                opType = 0;
                break;
            case ">":
                opType = 1;
                break;
            case "<":
                opType = 2;
                break;
            case "<>":
                opType = 3;
                break;
            case "<=":
                opType = 4;
                break;
            case ">=":
                opType = 5;
                break;
        }

        // Similar to the let event, if the variable that we are checking for starts
        // with a number, then we do not need to call Integer.parseInt all the time.
        // Just store the integer value!
        if (args1 - 'A' < 0){
            isVariable1 = false;
            argsInt1 = Integer.parseInt(input[0]);
        }
        if (args2 - 'A' < 0){
            isVariable2 = false;
            argsInt2 = Integer.parseInt(input[2]);
        }

        // And of course, don't forget to store the goto line.
        gotoLine = Integer.parseInt(input[5]);
    }

    @Override
    public void execute (Model model){
        int x, y;
        boolean outcome = false;

        // Set the variables. If we already know that the inputs to the conditional
        // are going to be non-numeric, we can simply pull out the values.
        if (isVariable1){
            x = model.getVar(args1);
        }
        else {
            x = argsInt1;
        }
        if (isVariable2){
            y = model.getVar(args2);
        }
        else {
            y = argsInt2;
        }

        // Run the statement based on what the input operator type was.
        switch (opType){
            case 0:
                outcome = (x == y);
                break;
            case 1:
                outcome = (x > y);
                break;
            case 2:
                outcome = (x < y);
                break;
            case 3:
                outcome = (x != y);
                break;
            case 4:
                outcome = (x <= y);
                break;
            case 5:
                outcome = (x >= y);
                break;
        }

        // If the statement is true, we take the jump!
        if (outcome){
            model.setPC(gotoLine);
        }

        // Else, we just continue program execution.
        else {
            model.setNextPC();
        }
    }
}

// SWE For the win!
// This class encapsulates a line of BASIC code in the input program.
abstract class Event implements Comparable<Event>{
    int numline;

    // Execute essentially executes the lines of code given the current state of
    // the computer as an input.
    abstract void execute(Model model);

    // Allows events to be compared to each other and ordered within the TreeMap.
    public int compareTo(Event other){
        return this.numline - other.numline;
    }
}

// This class encapsulates the data stored within the program.
// Technically the program itself shouldn't be in the model, but because I can (and
// it's easier to do certain things), I chose to put it in here.
class Model {
    private TreeMap<Integer, Event> program = new TreeMap<>();

    // Initialise the global variables necessary to the program.
    private int[] globals = new int[26];
    private int pc;

    // This is a flag that will be used in the driver program.
    private boolean isEndOfProgram = false;

    // This sets up the initial program counter. It just sets it to be the first
    // ever key in the program.
    public void init(){
        this.pc = program.firstKey();
    }

    // Method to add a new event into the program tree.
    public void putEvent (int numLine, Event event){
        program.put(numLine, event);
    }

    // Method to set the PC to a given value.
    // Useful for GOTO events.
    public void setPC(int pc){
        this.pc = pc;
    }

    // Gets the next PC by moving through the keys in the tree.
    // Also, it does a simple check to see if the program has terminated already.
    public void setNextPC(){
        Integer nextPc = program.higherKey(pc);
        if (nextPc == null){
            isEndOfProgram = true;
        }
        else {
            pc = nextPc;
        }
    }

    // Method that exposes the isEndOfProgram flag to the outside world.
    public boolean hasProgramEnded(){
        return isEndOfProgram;
    }

    // Sets the value of a particular variable.
    public void setVar(char variable, int newValue){
        globals[variable - 'A'] = newValue;
    }

    // Gets the value of a particular variable.
    public int getVar(char variable){
        return globals[variable - 'A'];
    }

    // Gets the event that is pointed to by the current PC.
    public Event getEvent(){
        return program.get(pc);
    }
}

// Main driver class for the program
public class BASICInterpreter{

    // This method parses the input string and converts it into a proper event
    // We only want to extract the type of event, so we split it into 2 parts
    public Event parseEvent(String input){
        String[] dlist = input.split(" ", 2);
        switch (dlist[0]){
            case "LET":
                return new LetEvent(dlist[1]);
            case "PRINT":
                return new PrintEvent(dlist[1], false);
            case "PRINTLN":
                return new PrintEvent(dlist[1], true);
            case "IF":
                return new IfEvent(dlist[1]);

            // This is needed so that Java doesn't complain that there's no return value.
            default:
                throw new IllegalArgumentException("Boi");
        }
    }

    public void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String in = r.readLine();

        Model model = new Model();

        // Keep scanning the input until we have reached the end of the line.
        while (in != null){
            // We want to extract out the linenumber, so we split it into 2 parts
            String[] dlist = in.split(" ", 2);
            model.putEvent(Integer.parseInt(dlist[0]), parseEvent(dlist[1]));
            in = r.readLine();
        }

        // Initialise the model. Essentially set the PC to be the correct first
        // value of the program to be run
        model.init();

        // While we have not reached the end of the program, get each event and
        // execute it with the model passed into it as the parameter.
        while (!model.hasProgramEnded()){
            model.getEvent().execute(model);
        }
    }

    public static void main(String[] args) throws IOException{
        BASICInterpreter basic = new BASICInterpreter();
        basic.run();
    }
}
