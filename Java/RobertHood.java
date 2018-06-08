import java.util.*;
import java.io.*;

// Set up my point class with all the getter functions
class Point implements Comparable<Point>{
    private int x;
    private int y;

    public Point (int x, int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return this.x;
    }

    public int getY(){
        return this.y;
    }

    public double distance(Point other){
        int dx = this.x - other.x;
        int dy = this.y - other.y;
        return Math.hypot(dx, dy);
    }

    @Override
    public int compareTo(Point other){
        if (this.x == other.x){
            return this.y - other.y;
        }
        return this.x - other.x;
    }

    @Override
    public boolean equals(Object o){
        if (!(o instanceof Point)){
            return false;
        }
        Point other = (Point) o;
        if (other.x == this.x && other.y == this.y){
            return true;
        }
        return false;
    }

    public void print(){
        System.out.printf("%d, %d\n", this.x, this.y);
    }
}

// Set up my ConvexHull class
class ConvexHull{
    Point[] hull;
    int size;
    // Returns the cross product of the two points A and B wrt point O.
    // The negative value lets us know that there was a counter clockwise turn.
    private static double cross (Point O, Point A, Point B){
        return (A.getX() - O.getX())*(B.getY() - O.getY()) -
               (A.getY() - O.getY())*(B.getX() - O.getX());
    }

    // Public constructor for the convex hull
    // Since its guaranteed that plist will have at least 2 points, we can skip
    // the check in this question.
    public ConvexHull (Point[] plist, int inputSize){
        hull = new Point[inputSize * 2];
        int midpoint = 0;

        Arrays.sort(plist);

        // Build the lower hull
        for (int toadd=0; toadd<inputSize; ++toadd){
            while (midpoint >= 2 &&
                   cross(hull[midpoint-2], hull[midpoint-1], plist[toadd]) <= 0){
                midpoint--;
            }
            hull[midpoint] = plist[toadd];
            midpoint++;
        }

        // Store the current length and build the upper hull
        int lowerHullBoundary = midpoint + 1;
        for (int toadd = inputSize-2; toadd>=0; --toadd){
            while (midpoint >= lowerHullBoundary &&
                   cross(hull[midpoint-2], hull[midpoint-1], plist[toadd]) <= 0){
                midpoint--;
            }
            hull[midpoint] = plist[toadd];
            midpoint++;
        }

        // Well we are guaranteed that the size of the hull will be at least 2.
        this.size = midpoint - 1;
    }

    // Performs rotating calipers on the set of points in the chull.
    public double rotatingCalipers(){
        double globalbest = 0;
        int otherpoint = 1;

        // For each point around the chull
        for (int i=0; i<this.size; ++i){
            Point curr = hull[i];
            double bestsofar = 0;
            double currbest = curr.distance(hull[otherpoint]);

            // Keep moving the other point around the chull while best increases
            while (currbest > bestsofar){
                bestsofar = currbest;
                otherpoint++;

                // Don't forget to check for overflows
                if (otherpoint == this.size){
                    otherpoint = 0;
                }

                currbest = curr.distance(hull[otherpoint]);
            }

            otherpoint--;
            if (otherpoint < 0){
                otherpoint += this.size;
            }

            if (bestsofar > globalbest){
                globalbest = bestsofar;
            }
        }

        return globalbest;
    }
}

// Main class
public class RobertHood{
    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int C = Integer.parseInt(r.readLine());
        HashSet<Point> phash = new HashSet<>();

        for (int i=0; i<C; ++i){
            String[] dlist = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);
            phash.add(new Point(x, y));
        }

        if (phash.size() == 1){
            System.out.println("0.0");
            return;
        }

        // Make the convex hull and then do rotating calipers
        ConvexHull chull = new ConvexHull(phash.toArray(new Point[0]), phash.size());
        System.out.println(chull.rotatingCalipers());
    }

    public static void main(String[] args) throws IOException{
        RobertHood robert = new RobertHood();
        robert.run();
    }
}
