import java.io.*;
import java.util.*;

class Person implements Comparable<Person>{
    String name;
    int num;
    int skill;

    public Person(String name, int skill, int num){
        this.name = name;
        this.skill = skill;
        this.num = num;
    }

    public int compareTo(Person other){
        if (this.skill == other.skill) return this.name.compareTo(other.name);
        return this.skill < other.skill ? 1 : -1;
    }
}

public class RaidTeam{
    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        OutputStream out = new BufferedOutputStream (System.out);

        // We create three PQs for the 3 skills
        PriorityQueue<Person> skill1 = new PriorityQueue<>();
        PriorityQueue<Person> skill2 = new PriorityQueue<>();
        PriorityQueue<Person> skill3 = new PriorityQueue<>();

        int n = Integer.parseInt(r.readLine());
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            skill1.add(new Person(dlist[0], Integer.parseInt(dlist[1]), i));
            skill2.add(new Person(dlist[0], Integer.parseInt(dlist[2]), i));
            skill3.add(new Person(dlist[0], Integer.parseInt(dlist[3]), i));
        }

        // Initialize data structures:
        boolean[] used = new boolean[n];

        // Keep popping for each of the 3 skills
        while (n >= 3){
            String[] output = new String[3];

            Person curr = skill1.poll();
            while (used[curr.num]){
                curr = skill1.poll();
            }
            used[curr.num] = true;
            output[0] = curr.name;

            curr = skill2.poll();
            while (used[curr.num]){
                curr = skill2.poll();
            }
            used[curr.num] = true;
            output[1] = curr.name;

            curr = skill3.poll();
            while (used[curr.num]){
                curr = skill3.poll();
            }
            used[curr.num] = true;
            output[2] = curr.name;

            // Sort the names
            Arrays.sort(output);

            for (String name : output){
                out.write(name.getBytes());
                out.write(' ');
            }
            out.write('\n');

            n -= 3;
        }

        // Then flush!
        out.flush();
    }

    public static void main(String[] args) throws IOException{
        RaidTeam raidTeam = new RaidTeam();
        raidTeam.run();
    }
}

