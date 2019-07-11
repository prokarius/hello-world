import java.io.*;
import java.util.*;

// This thing encapsulates a range. We will need this to check if a line segment is
// contained within a circle.
class Range implements Comparable<Range>{
    double start;
    double end;

    // Make it so that start < end
    public Range (double start, double end){
        this.start = start;
        this.end = end;
    }

    public int compareTo(Range other){
        return (this.start > other.start)?(1):(-1);
    }
}

class Point{
    double x;
    double y;

    public Point (double x, double y){
        this.x = x;
        this.y = y;
    }

    public double distance(Point other){
        double dx = this.x - other.x;
        double dy = this.y - other.y;
        return Math.sqrt(dx*dx + dy*dy);
    }

    public boolean equals(Point other){
        return this.x == other.x && this.y == other.y;
    }
}

class Circle{
    Point p;
    double r;

    public Circle (double x, double y, double r){
        this.p = new Point(x, y);
        this.r = r;
    }

    // Returns true if the circles even touch
    boolean intersects(Circle other){
        if (other.p.distance(this.p) < this.r + other.r + 1e-8) return true;
        return false;
    }

    // Returns an array of (2) Points that are at the intersection of the two circles
    // Shamelessly ripped from: https://stackoverflow.com/questions/3349125/circle-circle-intersection-points
    Point[] intersectionPoints(Circle other){
        // Check if the circles are tangent. If they are, there is only
        // 1 intersection point!
        if (Math.abs(other.p.distance(this.p) - (this.r + other.r)) < 1e-8){
            Point[] intersections = new Point[1];
            double dx = this.p.x - other.p.x;
            double dy = this.p.y - other.p.y;
            double combinedr = this.r + other.r;

            double newX = other.p.x + dx * other.r / combinedr;
            double newY = other.p.y + dy * other.r / combinedr;

            intersections[0] = new Point(newX, newY);
            return intersections;
        }

        Point[] intersections = new Point[2];

        double x0 = this.p.x;
        double x1 = other.p.x;
        double y0 = this.p.y;
        double y1 = other.p.y;

        double d = this.p.distance(other.p);
        double a = (this.r*this.r - other.r*other.r + d*d)/(2*d);
        double h = Math.sqrt(this.r*this.r - a*a);
        double x2 = x0 + a*(x1 - x0)/d;
        double y2 = y0 + a*(y1 - y0)/d;

        double x3 = x2 + h*(y1 - y0)/d;
        double y3 = y2 - h*(x1 - x0)/d;
        double x4 = x2 - h*(y1 - y0)/d;
        double y4 = y2 + h*(x1 - x0)/d;

        intersections[0] = new Point(x3, y3);
        intersections[1] = new Point(x4, y4);

        return intersections;
    }

    // We also want a function that returns the range where a line intersects
    // the given circle.
    Range lineIntersection(Point start, Point end){

        // We check if there is an intersection in the first place.
        // Shamelessly ripped off http://paulbourke.net/geometry/pointlineplane/
        double x1 = start.x;
        double x2 = end.x;
        double x3 = this.p.x;
        double y1 = start.y;
        double y2 = end.y;
        double y3 = this.p.y;

        double dx = x1 - x2;
        double dy = y1 - y2;
        double d = dx*dx + dy*dy;

        double u = ((x3-x1)*(x2-x1) + (y3-y1)*(y2-y1)) / d;

        double x = x1 + u*(x2 - x1);
        double y = y1 + u*(y2 - y1);

        // Check if the point intersects at all
        double dist = new Point(x, y).distance(this.p);
        if (dist > this.r){
            return null;
        }

        // Else return a range. This range is essentially the where the line segment
        // will cut the circle.
        // Note that the hypotenuse of the circle is essentially the radius of the
        // circle, so the adjacent distance is essentially sqrt(distance**2 - dist**2)
        double length = start.distance(end);
        double adj = this.r*this.r - dist*dist;

        // Small DUCT TAPE: if adj is less than 0, then we are screwed
        if (adj < 0){
            return null;
        }

        // Find the midpoint as a fraction of the line segment, and return the range
        double midPoint;
        if ((x2 - x1) != 0){
            midPoint = (x - x1) / (x2 - x1);
        }
        else {
            midPoint = (y - y1) / (y2 - y1);
        }

        double dFraction = Math.sqrt(adj) / length;
        return new Range(midPoint - dFraction - 1e-8 , midPoint + dFraction + 1e-8);
    }
}

class Edge{
    private int end;
    private double distance;

    public Edge(int end, double distance){
        this.end = end;
        this.distance = distance;
    }

    public int getEnd(){
        return this.end;
    }

    public double getDistance(){
        return this.distance;
    }
}

public class BearlyMadeIt{
    ArrayList<Point> points = new ArrayList<>();
    Circle[] circles;

    ArrayList<ArrayList<Edge>> adjList = new ArrayList<>();

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        String[] dlist = r.readLine().split(" ");

        Point start = new Point(Double.parseDouble(dlist[0]), Double.parseDouble(dlist[1]));
        Point end = new Point(Double.parseDouble(dlist[2]), Double.parseDouble(dlist[3]));

        // Push the start and ends into the points arrayList
        points.add(start);
        points.add(end);

        // Scan in the circles
        int inputCircles = Integer.parseInt(r.readLine());
        int numCircles = 0;
        circles = new Circle[inputCircles];

        for (int i = 0; i < inputCircles; ++i){
            dlist = r.readLine().split(" ");
            Point circleCenter = new Point(Double.parseDouble(dlist[0]), Double.parseDouble(dlist[1]));
            double radius = Double.parseDouble(dlist[2]);
            boolean flag = true;

            // Did you know there is a test case where they give you concentric
            // circles? What assholes.
            for (int j = 0; j < numCircles; ++j){
                if (circleCenter.equals(circles[j].p)){
                    flag = false;

                    // Check which circle has a larger radius
                    if (radius > circles[j].r){
                        circles[j] = new Circle(circleCenter.x, circleCenter.y, radius);
                    }

                    break;
                }
            }
            // Only add the new circle to the end of the list when we did not short circuit
            if (flag){
                circles[numCircles] = new Circle(circleCenter.x, circleCenter.y, radius);
                ++numCircles;
            }
        }

        // Find all the intersection points between the circles
        for (int i = 0; i < numCircles - 1; ++i){
            for (int j = i+1; j < numCircles; ++j){
                if (!circles[i].intersects(circles[j])) continue;
                Point[] intersections = circles[i].intersectionPoints(circles[j]);

                // There could only be 1 intersection point
                points.add(intersections[0]);
                if (intersections.length > 1){
                    points.add(intersections[1]);
                }
            }
        }

        int numPoints = points.size();

        // Initialise the adjList
        for (int i = 0; i < numPoints; ++i){
            adjList.add(new ArrayList<>());
        }

        // Of course, we need to check for our first 2 points too...
        // This one is more of a pain...
        for (int i = 0; i < numPoints-1; ++i){
            Point firstPoint = points.get(i);
            for (int j = i+1; j < numPoints; ++j){
                Point secondPoint = points.get(j);

                // We store the ranges so we can do sliding window
                ArrayList<Range> ranges = new ArrayList<>();

                // Find out where each circle intersect the line (if it does)
                for (int k = 0; k < numCircles; ++k){
                    Range range = circles[k].lineIntersection(firstPoint, secondPoint);
                    if (range == null) continue;
                    ranges.add(range);
                }

                // OK we now have a list of ranges, sort the ranges, and do a sliding
                // window to see if the entire range from 0 to 1 has been covered
                Collections.sort(ranges);

                double currPos = 1e-8;
                for (Range range: ranges){
                    if (range.start > currPos) break;
                    if (range.end < currPos) continue;
                    currPos = range.end;
                }

                if (currPos < 1){
                    continue;
                }

                // Else add the edge in both directions
                double distance = firstPoint.distance(secondPoint);
                adjList.get(i).add(new Edge(j, distance));
                adjList.get(j).add(new Edge(i, distance));
            }
        }

        // Lastly, run dijkstra. We will do inefficient dijkstra because it is
        // faster on a complete graph: O(V2) instead of O(E log V)

        // Initialise the distance array
        double[] distance = new double[numPoints];
        distance[0] = 0;
        for (int i = 1; i < numPoints; ++i){
            distance[i] = 1e30;
        }

        boolean[] processed = new boolean[numPoints];

        // Now we do dijkstra.
        while(true){
            int toProcess = -1;
            double best = 1e25;

            // Find the next point to process, which is the point that hasn't been
            // processed before that has the smallest distance
            for (int i = 0; i < numPoints; ++i){
                if (!processed[i] && distance[i] < best){
                    toProcess = i;
                    best = distance[i];
                }
            }

            // If we did not find a point, then break
            if (toProcess == -1) break;

            // If not, process the point by setting the distance to all other points
            processed[toProcess] = true;
            for (Edge edge : adjList.get(toProcess)){
                distance[edge.getEnd()] = Math.min(distance[edge.getEnd()], distance[toProcess] + edge.getDistance());
            }
        }

        // Cool now that we are done with dijkstra, if we have not visited the first
        // point, we print "impossible". If not we print the distance
        if (distance[1] > 1e25){
            System.out.println("impossible");
        }
        else {
            System.out.println(distance[1]);
        }
    }

    public static void main(String[] args) throws IOException{
        BearlyMadeIt bear = new BearlyMadeIt();
        bear.run();
    }
}

