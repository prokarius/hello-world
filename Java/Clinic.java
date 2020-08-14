import java.io.*;
import java.util.*;

public class Clinic{

    // Hey look, Im using class encapsulation today for some reason
    class Person implements Comparable<Person>{
        int id;
        long priority;
        String name;

        public Person(int id, long priority, String name){
            this.id = id;
            this.priority = priority;
            this.name = name;
        }

        public int compareTo(Person other){
            if (this.priority != other.priority){
                return (this.priority < other.priority)?(1):(-1); 
            }
            return (this.name.compareTo(other.name));
        }
    }

    PriorityQueue<Person> pq = new PriorityQueue<>();
    HashMap<String, Integer> mapping = new HashMap<>();
    int numPeople = 0;
    boolean[] ded;

    private void run() throws IOException{
        // Large output... Oh shit, is it time for oooo? 
        OutputStream log = new BufferedOutputStream (System.out);
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int n = Integer.parseInt(dlist[0]);
        long K = Long.parseLong(dlist[1]);  // long long is a plague

        // Set up the ded array
        ded = new boolean[n];

        for (int i = 0; i < n; ++i){
            dlist = r.readLine().split(" ");

            int queryType = Integer.parseInt(dlist[0]);
            switch (queryType){

                // Process a new person
                case 1:
                    int t = Integer.parseInt(dlist[1]);
                    int s = Integer.parseInt(dlist[3]);

                    // Add him to mapping
                    mapping.put(dlist[2], numPeople);

                    // Add him to pqueue
                    long priority = s - K*t;
                    pq.add(new Person(numPeople, priority, dlist[2]));
                    numPeople++;
                    break;

                // Outprocess a person
                case 2:
                    // Ok well, outpro a person that is not ded
                    Person curr = pq.poll();
                    while (curr != null && ded[curr.id]){
                        curr = pq.poll();
                    }

                    // Is clinic taking a break?
                    if (curr == null){
                        log.write("doctor takes a break\n".getBytes());
                        break;
                    }

                    log.write(curr.name.getBytes());
                    log.write('\n');
                    break;

                // Oh no, the guy got bored and left!
                case 3:
                    // Set that he has died.
                    int id = mapping.get(dlist[2]);
                    ded[id] = true;
                    break;
            }

            // Everyone is fun to flush
            log.flush();
        }
    }

    public static void main(String[] args) throws IOException{
        Clinic clinic = new Clinic();
        clinic.run();
    }
}

