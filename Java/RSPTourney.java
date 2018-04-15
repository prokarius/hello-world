import java.util.*;
import java.io.*;

class Player{
    private int wins;
    private int total;

    public Player(){
        this.wins = 0;
        this.total = 0;
    }

    public void win(){
        this.wins++;
        this.total++;
    }

    public void lose(){
        this.total++;
    }

    public void print(){
        if (this.total == 0){
            System.out.println("-");
        }
        else {
            System.out.printf("%.3f\n", wins/((float) total));
        }
    }
}

// Simple simulation game.
public class RPS{
    private void run(int N, int K, BufferedReader r) throws IOException{
        Player[] players = new Player[N];
        for (int i=0; i<N; ++i){
            players[i] = new Player();
        }
        int totalgames = (K*(N-1)*N)/2;

        // Simulate the games
        for (int i=0; i<totalgames; ++i){
            String[] dlist = r.readLine().split(" ");
            Player player1 = players[Integer.parseInt(dlist[0])-1];
            Player player2 = players[Integer.parseInt(dlist[2])-1];
            simulate(player1, player2, dlist[1], dlist[3]);
        }

        // Print them out
        for (Player player : players){
            player.print();
        }
        System.out.printf("\n");
    }

    // Takes a string of "rock", "paper", or "scissors" and returns an int
    private int convert (String inputStr){
        int output;
        switch (inputStr){
            case "rock":
                output = 0;
                break;
            case "paper":
                output = 1;
                break;
            case "scissors":
                output = 2;
                break;
            default:
                output = 0;
        }
        return output;
    }

    // Input 2 Player objects, and two strings of "rock", "paper", or "scissors"
    // Updates the player state based on their choices
    private void simulate(Player one, Player two, String playerone, String playertwo){
        int player1 = convert(playerone);
        int player2 = convert(playertwo);

        switch ((3 + player1 - player2)%3){
            // Player 1 wins
            case 1:
                one.win();
                two.lose();
                break;

            // Player 2 wins
            case 2:
                one.lose();
                two.win();
                break;

            default:
                break;
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        RPS solution = new RPS();
        String[] nandk = r.readLine().split(" ");
        while (nandk.length > 1){
            int n = Integer.parseInt(nandk[0]);
            int k = Integer.parseInt(nandk[1]);
            solution.run(n, k, r);
            nandk = r.readLine().split(" ");
        }
    }
}

