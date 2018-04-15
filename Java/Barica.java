import java.util.*;
import java.io.*;

class Pair{
    int value;
    int parent;

    public Pair(int x, int y){
        this.value = x;
        this.parent = y;
    }
}

class Plant{
    public static int ID = 0;
    public int id;
    public int x;
    public int y;
    public int f;
    public int best;

    public Plant(int x, int y, int f){
        this.id = this.ID;
        this.x = x;
        this.y = y;
        this.f = f;
        this.ID++;
    }

    public void setBest(int best){
        this.best = best;
    }

    public void print(OutputStream log) throws IOException{
        log.write(String.valueOf(this.x).getBytes());
        log.write(' ');
        log.write(String.valueOf(this.y).getBytes());
        log.write('\n');
        log.flush();
    }
}

public class Barica{
    private LinkedList<Plant> jumps = new LinkedList<>();
    private TreeMap<Integer, ArrayList<Plant>> xcoord = new TreeMap<>();
    private ArrayList<Pair> dpx = new ArrayList<>(100005);
    private ArrayList<Pair> dpy = new ArrayList<>(100005);
    private ArrayList<Integer> parent = new ArrayList<>();
    private ArrayList<Plant> cache = new ArrayList<>();

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] nandk = r.readLine().split(" ");
        int n = Integer.parseInt(nandk[0]);
        int k = Integer.parseInt(nandk[1]);

        // Set up the dp arrayLists
        for (int i=0; i<100002; ++i){
            dpx.add(new Pair(0,0));
            dpy.add(new Pair(0,0));
        }

        // Find who is plant 1, and store the data
        String[] dlist = r.readLine().split(" ");
        int x1 = Integer.parseInt(dlist[0]);
        int y1 = Integer.parseInt(dlist[1]);
        int f = Integer.parseInt(dlist[2]);
        Plant next = new Plant(x1, y1, f);

        // Add plant 1 to our TreeMap thing
        xcoord.put(x1, new ArrayList<>());
        xcoord.get(x1).add(next);

        // Say that it has f units of energy to begin with
        parent.add(0);
        cache.add(next);

        dpx.set(x1, new Pair(k, 0));
        dpy.set(y1, new Pair(k, 0));

        for (int i=1; i<n; ++i){
            dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);
            f = Integer.parseInt(dlist[2]);

            // If the x coord or y coord is smaller than plant 1, we will
            // never be able to reach there. don't even bother.
            // By doing this, we can ensure that plant 1 is at always
            // at the bottom left corner.
            if (x < x1 || y < y1){
                continue;
            }

            // If we will be able to reach it, create the plant
            next = new Plant(x, y, f);

            // Index the plants. Each plant has a unique ID
            // We will push each plan into 2 hashmap of arrayLists
            // This corresponds to their x and y coordinates
            if (xcoord.get(x) == null){
                xcoord.put(x, new ArrayList<>());
            }
            xcoord.get(x).add(next);

            parent.add(-1);
            cache.add(next);

            // Add to the DP HashMaps
            if (dpx.get(x) == null){
                dpx.set(x, new Pair (-2000000000, -1));
            }

            if (dpy.get(y) == null){
                dpy.set(y, new Pair (-2000000000, -1));
            }
        }

        // Now that we have scanned in all the plants, we need to sort all the
        // items in both hashmaps.
        for (int key : xcoord.keySet()){
            Collections.sort(xcoord.get(key), (Plant a, Plant b) -> a.y - b.y);
        }

        // Now we run DP from the bottom left.
        // key runs through all the keys in ascending order
        for (int key : xcoord.keySet()){
            for (Plant curr: xcoord.get(key)){
                int x = curr.x;
                int y = curr.y;
                f = curr.f;
                int id = curr.id;

                // Find which dp is the best one
                int dpbest;
                int currparent;
                if (dpx.get(x).value > dpy.get(y).value){
                    dpbest = dpx.get(x).value - k;
                    currparent = dpx.get(x).parent;
                }
                else {
                    dpbest = dpy.get(y).value - k;
                    currparent = dpy.get(y).parent;
                }

                // But wait, if the dpbest is negative, it means we don't have
                // energy to jump! In that case, just ignore it.
                if (dpbest < 0){
                    continue;
                }

                // Nom the flies.
                dpbest += f;

                // Set the parent of the current node to be the current parent
                parent.set(id, currparent);
                curr.setBest(dpbest);

                // If not, then we'll see if this increases the dp of the row:
                if (dpbest > dpx.get(x).value){
                    dpx.set(x, new Pair (dpbest, id));
                }

                if (dpbest > dpy.get(y).value){
                    dpy.set(y, new Pair (dpbest, id));
                }
            }
        }

        // Print the shit
        OutputStream log = new BufferedOutputStream (System.out);
        int last = Plant.ID-1;
        int bestEnergy = cache.get(last).best;
        while (parent.get(last) != last){
            jumps.addFirst(cache.get(last));
            last = parent.get(last);
        }
        jumps.addFirst(cache.get(last));
        System.out.println(bestEnergy);
        System.out.println(jumps.size());
        for (Plant plant: jumps){
            plant.print(log);
        }
    }

    public static void main(String[] args) throws IOException{
        Barica barica = new Barica();
        barica.run();
    }
}

