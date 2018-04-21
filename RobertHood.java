import java.util.*;

// Encapsulates a point
class Point implements Comparable<Point>{
    private int x;
    private int y;

    // Method to create a point.
    public Point(int a, int b){
        this.x = a;
        this.y = b;
    }

    // Returns the distance between the current point and the input
    public double dist(Point one){
        return Math.hypot(one.x - this.x, one.y - this.y);
    }

    // Returns the direction of cross product of input, with respect to this;
    // If this function is positive, the directions are counter clockwise.
    public double counterclock(Point a, Point b){
        return (a.x - this.x)*(b.y - this.y) - (a.y - this.y)*(b.x - this.x);
    }
}

// Ripped from Wikibooks.
// Andrew's Monotone Chain algo
public class ConvexHull {
    // Returns the cross product of points
    private static long cross(Point origin, Point a, Point b){
        return (a.getX() - origin.getX()) * (b.getY() - origin.getY()) -
               (a.getY() - origin.getY()) * (b.getX() - origin.getX());
    }

    // Takes a arraylist of points, and creates a convex hull
    public static ArrayList<Point> convexhull(ArrayList<Point> pointList){
        for 

public class RobertHood{
    static ArrayList<Point> pointsList = new ArrayList<>();
    static ArrayList<Point> hull = new ArrayList<>();
    public static void main(String[] args){
        Scanner s = new Scanner(System.in);

        // Populate the points list with the input points
        int C = s.nextInt();
        int lowy = 1005;
        for (int i=0; i<C; ++i){
            int x = s.nextInt();
            int y = s.nextInt();
            lowy = (lowy < y) ? (lowy) : (y);
            Point newPoint = new Point (x, y);
            pointsList.add(newPoint);
        }

        // Push the point with the lowest y value into the list
        

        // Run a convex Hull algo
        // Using the lowest y value point, we sort by angle
        Collections.sort(pointsList, (a, b) -> {
                double hypotenuse = Math.hypot(a.x - low.x, a.y - low.y);
                return Math.acos((a.x - low.x)/hypotenuse);
        });

        // Push lowest y value point into the hull
        


        // Then do rotating calipers.

    }
}
