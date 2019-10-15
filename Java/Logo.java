import java.io.*;
import java.util.*;

// Use Kattis to train software engineering!
class Command{
  int amount;
  
  public Command(int amount){
    this.amount = amount;
  }
}

class TurnCommand extends Command{
  public TurnCommand(int amount){
    super(amount);
  }
}

class MoveCommand extends Command{
  public MoveCommand(int amount){
    super(amount);
  }
}

class Turtle {
    double x;
    double y;
    double angle;

    public Turtle(){
        this.x = 0;
        this.y = 0;
        this.angle = 0;
    }

    public void execute(Command command){
        // Move command
        if (command instanceof MoveCommand){
            this.x += Math.cos(this.angle) * command.amount;
            this.y += Math.sin(this.angle) * command.amount;
        }
        // Turn command
        else {
            this.angle += (Math.PI * command.amount) / 180;
        }
    }

    public int getDistanceFromHome(){
        return (int) Math.round(Math.sqrt(this.x * this.x + this.y * this.y));
    }
}

public class Logo{
    private void run(BufferedReader r) throws IOException{
        // Initialise turtle
        Turtle turtle = new Turtle();

        // Scan in input
        int numCommands = Integer.parseInt(r.readLine());
        Command[] commands = new Command[numCommands];

        for (int i = 0; i < numCommands; ++i){
            String[] dlist = r.readLine().split(" ");
            int amount = Integer.parseInt(dlist[1]);
            switch (dlist[0]){
                case "fd":
                    commands[i] = new MoveCommand(amount);
                    break;
                case "bk":
                    commands[i] = new MoveCommand(-amount);
                    break;
                case "rt":
                    commands[i] = new TurnCommand(amount);
                    break;
                case "lt":
                    commands[i] = new TurnCommand(-amount);
                    break;
            }
        }

        // Execute the commands
        for (int i = 0; i < numCommands; ++i){
            turtle.execute(commands[i]);
        }

        System.out.println(turtle.getDistanceFromHome());
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());

        for (int i = 0; i < testcases; ++i){
            Logo logo = new Logo();
            logo.run(r);
        }
    }
}

