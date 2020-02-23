import java.io.*;
import java.util.*;

public class Alehouse{
    class Event implements Comparable<Event>{
        int time;
        int type; // Enter event = 0, leave event = 1

        public Event (int time, int type){
            this.time = time;
            this.type = type;
        }

        // Runs an event and returns the number of people in the alehouse at time of running.
        int run(){
            // If this is a new guy coming in, we include him in the count
            if (this.type == 0){
                ++people;
                return people;
            }
            else { // this.type == 1
                --people;
                return people + 1;
            }
        }

        public int compareTo (Event other){
            if (this.time != other.time) return this.time - other.time;
            return this.type - other.type;
        }
    }

    int people = 0;

    PriorityQueue<Event> pqueue = new PriorityQueue<>();
    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        int k = Integer.parseInt(dlist[1]);

        // Scan in input and create 2 events for each input
        // We can simulate the person staying for k seconds by adding k seconds to
        // everyone else, making them stay k more seconds before leaving.
        for (int i = 0; i < n; ++i){
            dlist = r.readLine().split(" ");
            int start = Integer.parseInt(dlist[0]);
            int end = Integer.parseInt(dlist[1]);

            pqueue.add(new Event(start, 0));
            pqueue.add(new Event(end + k, 1));
        }

        // Pop all the events until the queue is empty, and return the max.
        int ans = 0;

        while (!pqueue.isEmpty()){
            ans = Math.max(ans, pqueue.poll().run());
        }

        System.out.println(ans);
    }

    public static void main(String[] args) throws IOException{
        Alehouse alehouse = new Alehouse();
        alehouse.run();
    }
}

