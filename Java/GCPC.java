import java.io.*;
import java.util.*;

public class GCPC{
    // It's a map of teams to their scores. But it's sorted by the score.
    // The sorted score is given by (qns << 44) - (penalty << 17) - teamNum
    TreeMap<Long, Integer> scoretree = new TreeMap<>();
    HashMap<Integer, Long> scoreboard = new HashMap<>();

    // This is just a set of teams that has higher score than mine.
    HashSet<Integer> betterTeams = new HashSet<>();

    // Also because we want fast I/O
    OutputStream log = new BufferedOutputStream (System.out);

    // Initialise all the teams in the competition.
    // They all have 0 questions, 0 time penalty. So they start with -i which is
    // their team number.
    private void init(int numTeams){
        for (int i = 1; i <= numTeams; ++i){
            scoretree.put((long) -i, i);
            scoreboard.put(i, (long) -i);
        }

        // Put in a sentinel value at the end of the tree
        scoretree.put(1L<<62, 0);
    }

    // Extracted out the method which would print the output after every event.
    private void addToPrintQueue() throws IOException{
        int pos = betterTeams.size() + 1;
        log.write(String.valueOf(pos).getBytes());
        log.write('\n');
    }

    // When my team scores, we see which teams to pop from the table.
    // We can do this by repeatedly calling nextHigher until the next higher node
    // is larger than what my score will be.
    private void myTeamEvent(long penalty){
        long currScore = scoreboard.get(1);
        long curr = currScore;
        long limit = curr + (1L << 44) - (penalty << 17);

        // For all the teams that now has a lower score, we can just pop them from
        // the set of all teams with greater score than mine.
        while (true){
            long next = scoretree.higherKey(curr);
            if (next > limit) break;
            int team = scoretree.get(next) % (1 << 17);
            betterTeams.remove(team);
            curr = next;
        }

        // Remove my current node and add it to the tree with the new score
        scoretree.remove(currScore);
        scoretree.put(limit, 1);
        scoreboard.put(1, limit);
    }

    // When another team scores, we check to see if they beat us
    // If they do, add them to the set of all better teams!
    private void otherTeamEvent(int team, long penalty){
        long oldTeamScore = scoreboard.get(team);
        long newTeamScore = oldTeamScore + (1L << 44) - (penalty << 17);
        if (newTeamScore > scoreboard.get(1)){
            betterTeams.add(team);
        }

        // Update the scoreboard and the tree.
        scoreboard.put(team, newTeamScore);
        scoretree.remove(oldTeamScore);
        scoretree.put(newTeamScore, team);
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int m = Integer.parseInt(dlist[1]);

        // Initialise all the teams
        init(n);

        // Process the events as they come in!
        for (int i = 0; i < m; ++i){
            String[] ph = r.readLine().split(" ");
            int teamNum = Integer.parseInt(ph[0]);
            long score = Long.parseLong(ph[1]);
            if (teamNum == 1) myTeamEvent(score);
            else otherTeamEvent(teamNum, score);
            addToPrintQueue();
        }

        // Actually print the stuff out
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        GCPC gcpc = new GCPC();
        gcpc.run();
    }
}
