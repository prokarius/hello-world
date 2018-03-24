import java.util.*;

// Encapsulates a point
class Point{
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
}

public class RobertHood{
    ArrayList<Point> pointsList = new ArrayList<>();
    public static void main(String[] args){
        Scanner s = new Scanner(System.in);

        // Populate the points list with the input points
        int C = s.nextInt();
        for (int i=0; i<C; ++i){
            Point newPoint = new Point (s.nextInt(), s.nextInt());
            pointsList.add(newPoint);
        }

        // Run a convex Hull algo



        // Then do rotating calipers.

    }

}
