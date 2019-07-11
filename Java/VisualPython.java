import java.io.*;
import java.util.*;

// Fenwick Tree class to encapsulate the overlap checking
// Apparently if it's integers, fenwick trees can do range query, range update
// Literally copied off GeekforGeeks
// I have no shame :<
class Fenwick{
    long[] fenwick;
    long[] fenwick2;
    int size;

    public Fenwick(int n){
        n++;
        fenwick = new long[n];
        fenwick2 = new long[n];
        this.size = n;
    }

    private int LSOne(int i){
        return (i & -i);
    }

    private void update(long[] tree, int location, long value){
        while (location < this.size){
            tree[location] += value;
            location += LSOne(location);
        }
    }

    private long rsq(long[] tree, int end){
        long sum = 0;
        while (end > 0){
            sum += tree[end];
            end -= LSOne(end);
        }
        return sum;
    }

    private long rsq(int end){
        return rsq(fenwick, end) * end - rsq(fenwick2, end);
    }

    public void update(int start, int end, long value){
        update(fenwick, start, value);
        update(fenwick, end+1, -value);

        update(fenwick2, start, value*(start-1));
        update(fenwick2, end+1, value*(-end));
    }

    public long rsq(int start, int end){
        return rsq(end) - rsq(start - 1);
    }
}

// Encapsulates a coordinate
class Coordinate{
    int x;
    int y;

    public Coordinate (int x, int y){
        this.x = x;
        this.y = y;
    }
}

// Encapsulates an event that will be pushed into the event queue
class Event implements Comparable<Event>{
    int id;
    int x;
    int y;
    int type; // 1 for add, 2 for delete

    public Event(int id, int x, int y, int type){
        this.id = id;
        this.x = x;
        this.y = y;
        this.type = type;
    }

    // Sorts by x value, then by y in event of a tie.
    public int compareTo (Event other){
        if (this.x == other.x){
            return this.y - other.y;
        }
        return this.x - other.x;
    }
}

// Yes I know I could have polymorphism somethign here, but Im a bit lazy
// Spare me
class FenwickEvent implements Comparable<FenwickEvent>{
    int start;
    int end;
    int x;
    int type;

    public FenwickEvent (int start, int end, int x, int type){
        this.start = start;
        this.end = end;
        this.x = x;
        this.type = type;
    }

    // Sorts be x value, then has all the add events come first, before the deletes
    // But we need to also compare based on y value too.
    public int compareTo (FenwickEvent other){
        if (this.x == other.x){
            return other.type - this.type;
        }
        return this.x - other.x;
    }
}

public class VisualPython{
    // For some reason, I want to store the coordinates as they are being added
    Coordinate[] topLeft;
    Coordinate[] bottomRight;
    Coordinate[] combined;

    // This will map the actual y value to the normalized y value
    HashMap<Integer, Integer> mappings = new HashMap<>();

    // I want to save the matchings as well
    int[] match;

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        int n = Integer.parseInt(r.readLine());

        topLeft = new Coordinate[n+1];
        bottomRight = new Coordinate[n+1];
        combined = new Coordinate[2*n];

        match = new int[n+1];

        for (int i = 0; i < n;){
            String[] dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);

            combined[i] = new Coordinate(x, y);
            ++i;
            topLeft[i] = new Coordinate(x, y);
        }

        for (int i = 0; i < n;){
            String[] dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);

            combined[i+n] = new Coordinate(x, y);
            ++i;
            bottomRight[i] = new Coordinate(x, y);
        }

        // We want to normalize the y axis. So we sort by y axis and assign the new
        // y values to each of these coordinates
        Arrays.sort(combined, (first, second) -> first.y - second.y);

        // Now we create the mapping table:
        int currY = -1000000007;
        int newY = 1;
        for (int i = 0; i < 2*n; ++i){
            if (combined[i].y != currY){
                mappings.put(combined[i].y, newY);
                currY = combined[i].y;
                ++newY;
            }
        }

        // And we update the values of the coordinates with the mappings from the
        // mapping table
        for (int i = 1; i <= n; ++i){
            topLeft[i].y = mappings.get(topLeft[i].y);
            bottomRight[i].y = mappings.get(bottomRight[i].y);
        }

        // OK now we gotta populate the event queue
        PriorityQueue<Event> eventQueue = new PriorityQueue<>();
        for (int i = 1; i <= n; ++i){
            eventQueue.add(new Event(i, topLeft[i].x, topLeft[i].y, 1));
            eventQueue.add(new Event(i, bottomRight[i].x, bottomRight[i].y, 2));
        }

        // We need a treeset to see all the points in play
        TreeSet<Coordinate> inPlay = new TreeSet<>((first, second) -> first.y - second.y);

        // Process each event.
        while (!eventQueue.isEmpty()){
            Event curr = eventQueue.poll();

            // If event is an ADD event, add the coordinate to the treeset
            if (curr.type == 1){
                // We need to check that there is not another coordinate with the
                // same y coord as the current one
                Coordinate nextLower = inPlay.floor(new Coordinate(1000007, curr.y));

                if (nextLower != null && nextLower.y == curr.y){
                    System.out.println("syntax error");
                    return;
                }

                inPlay.add(new Coordinate(curr.id, curr.y));
            }

            // If event is a DELETE event, find the smallest y value that matches
            if (curr.type == 2){
                Coordinate lowest = inPlay.floor(new Coordinate(0, curr.y));

                // Now if there is no such element, lowest will be null, and we can
                // say this is a syntax error
                if (lowest == null){
                    System.out.println("syntax error");
                    return;
                }

                int topLeftID = lowest.x;
                int bottomRightID = curr.id;
                match[topLeftID] = bottomRightID;
                inPlay.remove(lowest);
            }
        }

        // AWESOME we are out of the stupid event processing.
        // If we are here, we have managed to match all the top left brackets to the
        // bottom right ones.
        // We just need to make sure they do not overlap

        // THIS IS WHERE MY STUPID FENWICK TREE COMES IN
        Fenwick fenwick = new Fenwick(200005);

        // Repush all the events into the event queue
        // This time the x and y of the events are the start and end of the rectangle
        PriorityQueue<FenwickEvent> fenwickEventQueue = new PriorityQueue<>();
        for (int i = 1; i <= n; ++i){
            // If the point is degenerate in the y direction, just add the "add" and
            // "delete" events
            if (topLeft[i].x == bottomRight[match[i]].x){
                fenwickEventQueue.add(new FenwickEvent(topLeft[i].y, bottomRight[match[i]].y, topLeft[i].x, 1));
                fenwickEventQueue.add(new FenwickEvent(topLeft[i].y, bottomRight[match[i]].y, topLeft[i].x+1, 2));
                continue;
            }
            fenwickEventQueue.add(new FenwickEvent(topLeft[i].y, bottomRight[match[i]].y, topLeft[i].x, 1));
            fenwickEventQueue.add(new FenwickEvent(topLeft[i].y+1, bottomRight[match[i]].y-1, topLeft[i].x+1, 2));
            fenwickEventQueue.add(new FenwickEvent(topLeft[i].y+1, bottomRight[match[i]].y-1, bottomRight[match[i]].x, 1));
            fenwickEventQueue.add(new FenwickEvent(topLeft[i].y, bottomRight[match[i]].y, bottomRight[match[i]].x+1, 2));
        }

        // Process the event
        while (!fenwickEventQueue.isEmpty()){
            FenwickEvent curr = fenwickEventQueue.poll();

            // Do not process the event if curr.start > curr.end
            // DUCT TAPE
            if (curr.start > curr.end) continue;

            // If event is an ADD event, check if there is an intersection with any rectangles
            if (curr.type == 1){
                if (fenwick.rsq(curr.start, curr.end) != 0){
                    System.out.println("syntax error");
                    return;
                }
                fenwick.update(curr.start, curr.end, 1);
            }

            // If event is a DELETE event, just update the fenwick tree
            if (curr.type == 2){
                fenwick.update(curr.start, curr.end, -1);
            }
        }

        // OK Shit we managed to get everything out. Time to print the stuff
        OutputStream log = new BufferedOutputStream (System.out);
        for (int i = 1; i <= n; ++i){
            log.write(String.valueOf(match[i]).getBytes());
            log.write('\n');
        }

        // FLUSH
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        VisualPython python = new VisualPython();
        python.run();
    }
}
