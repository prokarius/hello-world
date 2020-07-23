import java.io.*;
import java.util.*;

class Children{
    private int numChild;
    private int eggPos;
    private Stack<Integer> stack;

    public Children(int n){
        this.numChild = n;
        this.eggPos = 0;
        stack = new Stack<>();
        stack.add(0);
    }
    
    public void undo(int n){
        for (int i = 0; i < n; ++i){
            this.stack.pop();
        }
        this.eggPos = stack.peek();
    }

    public void toss(int n){
        this.eggPos = (this.eggPos + n + 100000 * this.numChild) % this.numChild;
        this.stack.add(this.eggPos);
    }

    public int getPos(){
        return this.eggPos;
    }
}

public class GameOfThrowns{
    Children children;

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int k = Integer.parseInt(dlist[1]);

        // Create the children instance
        children = new Children(n);

        dlist = r.readLine().split(" ");
        int curr = 0;

        for (int i = 0; i < k; ++i){
            if (dlist[curr].equals("undo")){
                curr++;
                int numUndo = Integer.parseInt(dlist[curr]);
                curr++;
                children.undo(numUndo);
            }
            else {
                int numToss = Integer.parseInt(dlist[curr]);
                curr++;
                children.toss(numToss);
            }
        }

        // Print where the egg last is
        System.out.println(children.getPos());
    }


    public static void main(String[] args) throws IOException{ 
        GameOfThrowns game = new GameOfThrowns();
        game.run();
    }
}
