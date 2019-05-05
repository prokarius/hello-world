import java.io.*;
import java.util.*;

class Coordinate{
    double longitude;
    double latitude;

    public Coordinate(double latitude, double longitude){
        this.latitude = latitude;
        this.longitude = longitude;
    }

    public double getLongitude(){
        return this.longitude;
    }

    public double getLatitude(){
        return this.latitude;
    }

    // Converts degrees to radians
    private double toRadians(double degrees){
        return degrees * Math.PI / 180;
    }

    // Gets the circular distance betweens two points
    // Dp some next level spherical trigo bullshit
    public double getDistance (Coordinate other){
        double dx = toRadians(this.getLatitude()) - toRadians(other.getLatitude());
        double dy = toRadians(this.getLongitude()) - toRadians(other.getLongitude());
        return 2 * Math.asin(Math.sqrt(
                    Math.sin(dx/2)*Math.sin(dx/2) +
                    Math.cos(toRadians(this.getLatitude()))*Math.cos(toRadians(other.getLatitude()))*
                            Math.sin(dy/2)*Math.sin(dy/2)));
    }
}

public class AirlineHub{
    private void solve(BufferedReader r, String input) throws IOException{
        int n = Integer.parseInt(input);
        ArrayList<Coordinate> coords = new ArrayList<>();

        // Scan in input    
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            double latitude = Double.parseDouble(dlist[0]);
            double longitude = Double.parseDouble(dlist[1]);
            coords.add(new Coordinate(latitude, longitude));
        }

        // If we only have 1 hub, return it
        if (n == 1){
            System.out.printf("%.2f %.2f\n", coords.get(0).getLatitude(), coords.get(0).getLongitude());
            return;
        }


        // Initialise and search for the best for each point.
        // If we manage to do better, update and move on
        double bestsofar = 1000000001;
        int bestIndex = n;
        for (int i = 0; i < n; ++i){
            double currBest = 0;
            for (int j = 0; j < n; ++j){
                if (i == j) continue;
                if (coords.get(i).getDistance(coords.get(j)) > currBest){
                    currBest = coords.get(i).getDistance(coords.get(j));
                }
            }

            // We advance the bestsofar index to the furthest we can too.
            if (bestsofar >= currBest){
                bestsofar = currBest;
                bestIndex = i;
            }
        }

        // Print that shit
        System.out.printf("%.2f %.2f\n", coords.get(bestIndex).getLatitude(), coords.get(bestIndex).getLongitude());
    }

    private void run() throws IOException{
        // Scan in input until EOF
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String input = r.readLine();
        while (input != null){
            solve(r, input);
            input = r.readLine();
        }
    }

    public static void main(String[] args) throws IOException{
        AirlineHub solution = new AirlineHub();
        solution.run();
    }
}

