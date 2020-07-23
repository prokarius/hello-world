import java.io.*;
import java.util.*;

class Floor implements Comparable<Floor>{
    int floor;
    int elevator;

    public Floor(int floor, int elevator){
        this.floor = floor;
        this.elevator = elevator;
    }

    public int compareTo (Floor other){
        return this.floor - other.floor;
    }
}

public class Hotels{

    ArrayList<Floor> floors = new ArrayList<>();
    int[][] adjmatrix;

    // For Dijkstra
    PriorityQueue<Floor> dijkstra = new PriorityQueue<>();
    int[] distance;

    private void run(BufferedReader r) throws IOException{   
        // Scan in input
        String[] dlist = r.readLine().split(" ");
        int f = Integer.parseInt(dlist[0]);
        int e = Integer.parseInt(dlist[1]);

        for (int i = 1; i <= e; ++i){
            // Populate all the floors in the building
            dlist = r.readLine().split(" ");
            int ri = Integer.parseInt(dlist[0]);
            int mi = Integer.parseInt(dlist[1]);

            while (ri < f){
                floors.add(new Floor(ri, i));
                ri += mi;
            }
        }

        // Set the bottom floor and top floor as their own elevators
        floors.add(new Floor(0, 0));
        floors.add(new Floor(f-1, e+1));

        // Initialise adjmatrix
        adjmatrix = new int[e+2][e+2];
        for (int i = 0; i < e+2; ++i){
            for (int j = 0; j < e+2; ++j){
                adjmatrix[i][j] = (1<<30) - 1;
            }
            adjmatrix[i][i] = 0;
        }

        // Sort all the floors, loop through them to find out distance between each
        // elevator set
        Collections.sort(floors);

        for (int i = 1; i < floors.size(); ++i){
            int elevatorSet1 = floors.get(i-1).elevator;
            int elevatorSet2 = floors.get(i).elevator;

            // Short circuit, if it's the same elevator set, give up
            if (elevatorSet1 == elevatorSet2) continue;


            int floor1 = floors.get(i-1).floor;
            int floor2 = floors.get(i).floor;

            if (floor2 - floor1 < adjmatrix[elevatorSet1][elevatorSet2]){
                adjmatrix[elevatorSet1][elevatorSet2] = floor2 - floor1;
                adjmatrix[elevatorSet2][elevatorSet1] = floor2 - floor1;
            }
        }

        // OK we have the adjmatrix, time to SSSP and doDijkstra
        distance = new int[e+2];
        for (int i = 0; i < e+2; ++i){
            distance[i] = (1<<30) - 1;
        }

        dijkstra.add(new Floor(0, 0));
        
        while (!dijkstra.isEmpty()){
            Floor curr = dijkstra.poll();
            int set = curr.elevator;
            int currDistance = curr.floor;

            // Short circuit: Have we been here before?
            if (distance[set] < currDistance) continue;

            for (int nextSet = 0; nextSet < e+2; ++nextSet){
                int newDistance = currDistance + adjmatrix[set][nextSet];

                // Short circuit: Can we get there using another shorter way?
                if (distance[nextSet] <= newDistance) continue;

                distance[nextSet] = newDistance;
                dijkstra.add(new Floor(newDistance, nextSet));
            }
        }

        // Right, we should have all the distances between elevators.
        // Now to iterate through all floors to find who has it worst.

        int best = 0;
        int bestFloor = 0;
        
        for (int i = 1; i < floors.size(); ++i){
            Floor higher = floors.get(i);
            Floor lower = floors.get(i-1);

            int delta = higher.floor - lower.floor;
            int lowerElevator = distance[lower.elevator]; 
            int higherElevator = distance[higher.elevator]; 
            int elevatorDelta = Math.abs(higherElevator - lowerElevator);

            // 2 Cases
            // Case 1: If the delta between the elevators is greater than the number
            // of floors between the elevators, then the worst floor is the one
            // furthest from the elevator with the smallest step count
            if (delta <= elevatorDelta){
                if (higherElevator < lowerElevator){
                    if (best < delta + higherElevator){
                        best = delta + higherElevator;
                        bestFloor = lower.floor;
                    }
                }
                else {
                    if (best < delta + lowerElevator){
                        best = delta + lowerElevator;
                        bestFloor = higher.floor;
                    }
                }
            }

            // Case 2: The delta is less than the difference between elevators
            else {
                // The number of floors left to climb is split the difference
                int floorsToClimb = (delta - elevatorDelta) / 2;
                if (best < floorsToClimb + Math.max(lowerElevator, higherElevator)){
                    best = floorsToClimb + Math.max(lowerElevator, higherElevator);

                    // The worst floor depends on which elevator is worst
                    if (lowerElevator > higherElevator){
                        bestFloor = lower.floor + floorsToClimb;
                    }
                    else {
                        bestFloor = higher.floor - (floorsToClimb + (delta - elevatorDelta)%2);
                    }
                }
            }
        }

        // Finally, we get to print that shit
        System.out.printf("%d %d\n", best, bestFloor);
    }


    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(r.readLine());

        while (t > 0){
            Hotels hotel = new Hotels();
            hotel.run(r);
            t--;
        }
    }
}

