import java.util.*;
import java.io.*;

class Point implements Comparable<Point>{
    private int x;
    private int y;

    public Point(int x, int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return this.x;
    }

    public int getY(){
        return this.y;
    }

    @Override
    public int compareTo (Point other){
        if (this.x == other.x){
            return this.y - other.y;
        }
        else {
            return this.x - other.x;
        }
    }
}

class ConvexHull{
    private ArrayList<Point> hull = new ArrayList<>();
    private int size;

    private static double cross (Point O, Point A, Point B){
        return (A.getX() - O.getX())*(B.getY() - O.getY()) -
               (A.getY() - O.getY())*(B.getX() - O.getX());
    }

    // Public constructor for the convex hull
    public ConvexHull (Point[] plist){
        // Now if the input array is of size 1, then there's nothing we can do.
        if (plist.length == 1){
            hull.add(plist[0]);
            size = 1;
        }

        // Else we can start to build stuff.
        else{
            // Set up the stuff
            int n = plist.length;
            Point[] phhull = new Point[2*n];
            int midpoint = 0;

            // Sort the array in increasing order
            Arrays.sort(plist);

            // Build the lower hull
            // For from the left end to the right, see if the next point forms
            // a counter clockwise turn from the previous
            for (int toadd=0; toadd<n; ++toadd){
                while (midpoint >= 2 &&
                       cross(phhull[midpoint-2], phhull[midpoint-1], plist[toadd]) <= 0){
                    midpoint--;
                }
                phhull[midpoint]= plist[toadd];
                midpoint++;
            }

            // Build the upper hull
            // Same thing, just that we do it backwards:
            int lowerHullBoundary = midpoint+1;
            for (int toadd=n-2; toadd>=0; --toadd){
                while (midpoint >= lowerHullBoundary &&
                       cross(phhull[midpoint-2], phhull[midpoint-1], plist[toadd]) <= 0){
                    midpoint--;
                }
                phhull[midpoint]= plist[toadd];
                midpoint++;
            }

            // OK we now gotta trim the convex hull
            if (midpoint > 1){
                size = midpoint-1;
                for (int i=0; i<size; ++i){
                    hull.add(phhull[i]);
                }
            }

            else {
                size = 0;
            }
        }
    }

    public double getArea(){
        // First check the size of the arraylist.
        if (this.size < 3){
            return 0.0;
        }

        double out = 0;

        // Choose a random point.
        Point start = this.hull.get(0);
        for (int i=1; i<this.size-1; ++i){
            out += cross(start, hull.get(i), hull.get(i+1));
        }

        return out/2;
    }
}

public class RobotProtection{
    private void run(BufferedReader r, int n) throws IOException{
        Point[] plist = new Point[n];
        for (int i=0; i<n; ++i){
            String[] dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);
            plist[i] = new Point (x, y);
        }

        ConvexHull chull = new ConvexHull (plist);
        System.out.println(chull.getArea());
    }

    public static void main(String[] args) throws IOException {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        RobotProtection robot = new RobotProtection();
        int n = Integer.parseInt(r.readLine());
        while (n != 0){
            robot.run(r, n);
            n = Integer.parseInt(r.readLine());
        }
    }
}
