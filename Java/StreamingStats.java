import java.io.*;
import java.util.*;

class FenwickTree {
    long[] tree;
    int size;
    
    public FenwickTree(int size){
        this.tree = new long[size];
        this.size = size;
    }

    public void update(int location, long value){
        for (int i = location; i < this.size; i += LSOne(i)){
            this.tree[i] += value;
        }
    }

    private long rsq(int end){
        long out = 0;
        for (int i = end; i > 0; i -= LSOne(i)){
            out += this.tree[i];
        }
        return out;
    }

    public long rsq(int start, int end){
        return rsq(end) - rsq(start);
    }

    private int LSOne(int x){
        return x&(-x);
    }
}

class Event implements Comparable<Event>{
    long time;
    int bitrate;

    public Event(long time, int bitrate){
        this.time = time;
        this.bitrate = bitrate;
    }

    public int compareTo(Event other){
        return this.time > other.time ? 1 : -1;
    }
}

public class StreamingStats{
    long[][] queries;
    FenwickTree tree;
    PriorityQueue<Event> events = new PriorityQueue<>();

    HashMap<Long, Integer> mapping = new HashMap<>();
    int idx = 1;

    int getMapping(long hash){
        if (mapping.containsKey(hash)){
            return mapping.get(hash);
        }
        mapping.put(hash, idx);
        return idx++;
    }

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream log = new BufferedOutputStream (System.out); 

        // Scan in input
        int n = Integer.parseInt(r.readLine());
        for (int i = 0; i < n; ++i){ 
            String[] dlist = r.readLine().split(" ");
            long end = Long.parseLong(dlist[0]);
            int duration = Integer.parseInt(dlist[1]);
            int bitrate = Integer.parseInt(dlist[2]);

            long start = end - duration;

            // Create the events
            events.add(new Event(start, bitrate));
            events.add(new Event(end, -bitrate));
        }

        int q = Integer.parseInt(r.readLine());
        queries = new long[q][2];
        for (int i = 0; i < q; ++i){
            String[] dlist = r.readLine().split(" ");
            long start = Long.parseLong(dlist[0]);
            long end = Long.parseLong(dlist[1]);
            queries[i][0] = start;
            queries[i][1] = end;

            events.add(new Event(start, 0));
            events.add(new Event(end, 0));
        }

        tree = new FenwickTree((n + q) * 2 + 7);

        // Map each event to a position in the Fenwick tree.
        // Then add the new value
        long currTime = -1;
        long totalBitRate = 0;
        while (!events.isEmpty()){
            Event event = events.poll();
            if (currTime == event.time){
                totalBitRate += event.bitrate;
                continue;
            }

            // If not, it's time to add a new entry in the FenwickTree
            int index = getMapping(event.time);
            long deltaTime = event.time - currTime;
            long memory = deltaTime * totalBitRate;

            tree.update(index, memory);

            currTime = event.time;
            totalBitRate += event.bitrate;
        }

        // Time to solve all the rsqs
        for (int i = 0; i < q; ++i){
            int start = getMapping(queries[i][0]);
            int end = getMapping(queries[i][1]);

            long out = tree.rsq(start, end);
        
            log.write(String.valueOf(out / 1000).getBytes());
            log.write('.');
            log.write(String.format("%03d", out % 1000).getBytes());
            log.write('\n');
        }

        // Print that shit
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        StreamingStats solution = new StreamingStats();
        solution.run();
    }
}

