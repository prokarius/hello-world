import java.io.*;
import java.util.*;

class Coordinate{
    int x;
    int y;

    public Coordinate (int x, int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return this.x;
    }

    public int getY(){
        return this.y;
    }

    // Returns Euclidean distance between this coordinate and the other coordinate
    public int getDistance(Coordinate other){
        int dx = this.x - other.x;
        int dy = this.y - other.y;
        return (dx * dx) + (dy * dy);
    }
}

public class Bakice{
    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        String[] dlist = r.readLine().split(" ");
        int R = Integer.parseInt(dlist[0]);
        int C = Integer.parseInt(dlist[1]);
        ArrayList<Coordinate> seats = new ArrayList<>();
        ArrayList<Coordinate> people = new ArrayList<>();

        // We need a hashset to keep track of which people and chair have exploded
        HashSet<Integer> explodedSeats = new HashSet<>();
        HashSet<Integer> explodedPeople = new HashSet<>();

        // Get the position of the people and the seats
        for (int i = 0; i < R; ++i){
            String line = r.readLine();
            for (int j = 0; j < C; ++j){
                if (line.charAt(j) == 'L'){
                    seats.add(new Coordinate(i, j));
                }
                else if (line.charAt(j) == 'X'){
                    people.add(new Coordinate(i, j));
                }
            }
        }

        // Also we need to sort too!
        TreeMap<Integer, ArrayList<Coordinate>> countingSort = new TreeMap<>();
        for (int i = 0; i <= 100; ++i){
            for (int j = i; j <= 100; ++j){
                if (countingSort.containsKey(i*i + j*j)) continue;
                countingSort.put(i*i + j*j, new ArrayList<>());
            }
        }

        // For each chair and rude passenger calculate the distance between them
        // Put their IDs into the corresponding bucket
        for (int i = 0; i < seats.size(); ++i){
            for (int j = 0; j < people.size(); ++j){
                int distance = seats.get(i).getDistance(people.get(j));
                countingSort.get(distance).add(new Coordinate(j, i));
            }
        }

        // Now, we sort and iterate
        int boom = 0;
        for (Integer distance : countingSort.keySet()){
            HashMap<Integer, ArrayList<Integer>> mapping = new HashMap<>();
            
            // Check to make sure the seats are not exploded yet
            for (Coordinate pair : countingSort.get(distance)){
                if (explodedSeats.contains(pair.getY())) continue;
                if (!mapping.containsKey(pair.getY())){
                    mapping.put(pair.getY(), new ArrayList<>());
                }
                mapping.get(pair.getY()).add(pair.getX());
            }

            // For each of the mappings, 
            for (Integer explodingSeat : mapping.keySet()){
                
                // Find all unexploded peopler
                HashSet<Integer> unexploded = new HashSet<>();
                for (Integer person : mapping.get(explodingSeat)){
                    if (explodedPeople.contains(person)) continue;
                    unexploded.add(person);
                }

                // If there are more than 2 people, boom boom
                if (unexploded.size() > 1) boom++;

                // If no one is gonna die, then it's fine
                if (unexploded.size() == 0) continue;

                // Blacklist the seats and the people
                explodedSeats.add(explodingSeat);
                for (Integer explodingPerson : unexploded){
                    explodedPeople.add(explodingPerson);
                }
            }
        }

        // Print that shit
        System.out.println(boom);
    }

    public static void main(String[] args) throws IOException{
        Bakice bakice = new Bakice();
        bakice.run();
    }
}
