import java.io.*;
import java.util.*;

// Class to encapsulate a coordinate.
class Coordinate implements Comparable<Coordinate>{
    private int x;
    private int y;
    private int id;
    private long distance;
    private Coordinate prev = null;

    public Coordinate (int x, int y, int id){
        this.x = x;
        this.y = y;
        this.id = id;
        this.distance = 1L << 62; // Init the distance to something ridiculous.
    }

    // Constructor for my PQ
    public Coordinate (long distance, int id){
        this.distance = distance;
        this.id = id;
    }

    // PQ Comparator
    public int compareTo(Coordinate other){
        if (this.distance > other.distance) return 1;
        return -1;
    }

    public long getDistanceTo(Coordinate other){
        long dx = (this.x - other.x);
        long dy = (this.y - other.y);
        return dx*dx + dy*dy;
    }

    // Getters and setters
    public int getID(){
        return this.id;
    }

    public long getDistance(){
        return this.distance;
    }

    public void setDistance(long newDistance){
        this.distance = newDistance;
    }

    public Coordinate getPrevious(){
        return this.prev;
    }

    public void setPrevious(Coordinate coord){
        this.prev = coord;
    }
}

public class TexasSummers{
    public void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        BufferedOutputStream log = new BufferedOutputStream(System.out);
        int n = Integer.parseInt(r.readLine());

        ArrayList<Coordinate> linkedlist = new ArrayList<>();
        ArrayList<Boolean> visited = new ArrayList<>();
        LinkedList<Integer> out = new LinkedList<>();
        PriorityQueue<Coordinate> dijkstra = new PriorityQueue<>();

        // Scan in the shady points and push to our arraylist of shady points
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);
            Coordinate shady = new Coordinate(x, y, i);
            linkedlist.add(shady);
            visited.add(false);
        }

        // Now scan in the start coordinate which will go to the front
        String[] dlist = r.readLine().split(" ");
        int x = Integer.parseInt(dlist[0]);
        int y = Integer.parseInt(dlist[1]);
        Coordinate shady = new Coordinate(x, y, n);
        shady.setDistance(0);
        linkedlist.add(shady);
        visited.add(false);

        // And the end coordinate which will go to the back
        dlist = r.readLine().split(" ");
        x = Integer.parseInt(dlist[0]);
        y = Integer.parseInt(dlist[1]);
        shady = new Coordinate(x, y, n+1);
        linkedlist.add(shady);
        visited.add(false);

        // Do dijkstra
        dijkstra.add(new Coordinate(0, n));
        int goalnum = n+1;

        while (!dijkstra.isEmpty()){
            int nextid = dijkstra.poll().getID();

            // Have we reached the goal?
            if (nextid == goalnum) break;


            // If we have visited this coordinate before, just continue
            // Else we set that we have visited it before.
            if (visited.get(nextid)) continue;
            visited.set(nextid, true);

            Coordinate next = linkedlist.get(nextid);
            long currDistance = next.getDistance();

            for (Coordinate coord : linkedlist){
                // Skip those coordinates that we have visited.
                if (visited.get(coord.getID())) continue;
                long newDistance = next.getDistanceTo(coord) + currDistance;

                // If it's nearer to go from here
                if (coord.getDistance() >= newDistance){
                    coord.setDistance(newDistance);
                    coord.setPrevious(next);
                    dijkstra.add(new Coordinate(newDistance, coord.getID()));
                }
            }
        }

        // If we are here, we have reached the classroom woohoo!
        // So we have reached the goal! yay!
        // Now we just gotta output all the entries.
        int count = 0;

        Coordinate goal = linkedlist.get(n+1);
        Coordinate paperTrail = goal.getPrevious();

        // Flag to see how many shady places I have been to
        int numshady = 0;

        while (paperTrail != null){
            ++numshady;
            out.addFirst(paperTrail.getID());
            paperTrail = paperTrail.getPrevious();
        }

        if (numshady < 2){
            System.out.println("-");
            return;
        }

        out.pollFirst();

        for (Integer id : out){
            log.write(String.valueOf(id).getBytes());
            log.write('\n');
        }

        // FLUSH!
        log.flush();
        return;
    }

    public static void main(String[] args) throws IOException{
        TexasSummers solution = new TexasSummers();
        solution.run();
    }
}
