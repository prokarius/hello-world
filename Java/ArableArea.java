import java.io.*;
import java.util.*;

class Point {
    private double x;
    private double y;

    public Point(double x, double y){
        this.x = x;
        this.y = y;
    }

    public double getX(){
        return this.x;
    }

    public double getY(){
        return this.y;
    }

    public int compareTo(Point other){
        if (this.x == other.x){
            return (this.y < other.y)?(1):(-1);
        }
        return (this.x < other.x)?(1):(-1);
    }
}

class Line implements Comparable<Line>{
    Point first;
    Point second;
    double gradient;

    // Ensure the lines have the first point < second.
    // This allows easy sorting by x coordinate
    public Line(Point first, Point second){
        if (first.compareTo(second) > 0){
            this.first = first;
            this.second = second;
        }
        else {
            this.first = second;
            this.second = first;
        }

        double dy = this.second.getY() - this.first.getY();
        double dx = this.second.getX() - this.first.getX();

        this.gradient = dy/dx;
    }

    // Given x, evaluate the y value where the line cuts the given x coordinate
    public double eval(double x){
        return (x - this.first.getX()) * this.gradient + this.first.getY();
    }

    public Point getFirst(){
        return this.first;
    }

    public Point getSecond(){
        return this.second;
    }

    // Compare by x value of the points first, then by y
    // This is for ordering of the lines
    public int compareTo(Line other){
        if (this.first.getX() == other.first.getX()){
            return (this.second.getX() < other.second.getX())?(-1):(1);
        }
        return (this.first.getX() < other.first.getX())?(-1):(1);
    }
}

public class ArableArea{
    PriorityQueue<Line> lineList = new PriorityQueue<>();
    ArrayList<Line> inPlay = new ArrayList<>();
    Point[] points = new Point[105];
    Line[] lines = new Line[105];

    private final double EPSILON = 1e-6;

    private void run(int n, BufferedReader r) throws IOException{

        // Scan in input
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            double x = Double.parseDouble(dlist[0]);
            double y = Double.parseDouble(dlist[1]);
            points[i] = new Point(x, y);
        }

        // Duplicate the last one for easy creation
        points[n] = points[0];

        // Create the linelist
        for (int i = 0; i < n; ++i){

            // Could be that the points are co-incident
            if (points[i].equals(points[i+1])) continue;

            // Else make the line, populate the line list
            lineList.add(new Line(points[i], points[i+1]));
        }

        // Pass in a sentinel value
        Point sentinelA = new Point(100005, 100005);
        Point sentinelB = new Point(200005, 200005);
        lineList.add(new Line(sentinelA, sentinelB));

        // Now we do a sweep line algorithm.
        int out = 0;

        // For each potential neighbouring pair of x value, see if a line is in play
        // We can do this by considering the midpoints
        // I don't want to deal with floating points here.
        for (int q = -199; q <= 199 ; q += 2){
            double currX = (double)q / 2;

            // Find all the lines in play, and add it to the arrayList
            while (lineList.peek().getFirst().getX() < currX){
                inPlay.add(lineList.poll());
            }

            // Get rid of all the points not in play
            ArrayList<Line> fromBefore = new ArrayList<>();
            for (Line currLine : inPlay){
                if (currLine.getSecond().getX() < currX) continue;
                fromBefore.add(currLine);
            }

            // Sort the current lineList based on the current x value
            Collections.sort(fromBefore, new Comparator<Line>(){
                public int compare(Line a, Line b){
                    return (a.eval(currX) < b.eval(currX))?(-1):(1);
                }
            });

            inPlay = fromBefore;

            // Now we can see how many squares are there in the current row.
            // Find the left and right x value.
            double left = (q-1)/2;
            double right = (q+1)/2;

            // For each pair of lines
            for (int i = 0; i < inPlay.size(); i += 2){
                Line bottomLine = inPlay.get(i);
                Line topLine = inPlay.get(i+1);

                // Find the top and bottom boundaries
                double topLeft = topLine.eval(left);
                double topRight = topLine.eval(right);

                double bottomLeft = bottomLine.eval(left);
                double bottomRight = bottomLine.eval(right);

                // Note that we want the minimum value of y for the top line
                // And the maximum value of y for the bottom line
                double minTop = (topLeft < topRight)?(topLeft):(topRight);
                double maxBottom = (bottomLeft > bottomRight)?(bottomLeft):(bottomRight);

                // This will tell us how many squares are bounded by the lines
                // i.e. Assuming only the lines are there, how many squares can be
                // forms (counting from the y-axis)
                int top = (int)Math.floor(minTop + EPSILON);
                int bottom = (int)Math.ceil(maxBottom - EPSILON);

                // Add the difference to the output, but only if there *are* squares
                out += (top > bottom)?(top - bottom):(0);
            }
        }

        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());

        while (n != 0){
            ArableArea solution = new ArableArea();
            solution.run(n, r);
            n = Integer.parseInt(r.readLine());
        }
    }
}
