import java.io.*;
import java.util.*;

class Point {
    int x;
    int y;

    public Point(int x, int y){
        this.x = x;
        this.y = y;
    }
}

class Equation {
    double a;
    double b;
    double c;
    double x;

    public Equation(int x, int a, int b, int c){
        this.x = x;
        this.a = a;
        this.b = b;
        this.c = c;
    }
}

public class PitchPerformance{

    static final double EPSILON = 1e-8;

    ArrayList<Point> pointList = new ArrayList<>();
    ArrayList<Equation> eqnList = new ArrayList<>();

    private double _getArea(Equation eqn, int y, double x){
        return eqn.a * x * x * x / 3.0 + eqn.b * x *x / 2.0 + (eqn.c - y) * x;
    }

    // If eqn is linear, find the area
    private double _linearIntegral(Equation eqn, int y, double x0, double x1){
        double intersection_point = (y - eqn.c) / eqn.b;

        // If there is an intersection point within range:
        if (x0 <= intersection_point && intersection_point <= x1){
            return Math.abs(_getArea(eqn, y, intersection_point) - _getArea(eqn, y, x0)) +
                   Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, intersection_point));
        }

        // If not we have just one path:
        return Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, x0));

    }

    private double _quadraticIntegral(Equation eqn, int y, double x0, double x1){
        // Find the determinant
        double p = eqn.b*eqn.b - 4*eqn.a*(eqn.c - y);

        // There is no intersection, or there is one intersection:
        if (p < EPSILON){
            return Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, x0));
        }

        // Else there are two intersections. Find them
        double firstIntersection = (-Math.sqrt(p) - eqn.b) / (2*eqn.a);
        double secondIntersection = (Math.sqrt(p) - eqn.b) / (2*eqn.a);

        // Oh crap, firstIntersection would be lower if a is negative. Flip it.
        if (firstIntersection > secondIntersection){
            double temp = secondIntersection;
            secondIntersection = firstIntersection;
            firstIntersection = temp;
        }

        // Are they within the x bounds?
        if (x1 <= firstIntersection || x0 >= secondIntersection){
            return Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, x0));
        }

        // Are the bounds even within x0s?
        if (firstIntersection <= x0 && x1 <= secondIntersection){
            return Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, x0));
        }


        // Are both within the range??
        if (x1 >= secondIntersection && x0 <= firstIntersection){
            return Math.abs(_getArea(eqn, y, firstIntersection) - _getArea(eqn, y, x0)) +
                   Math.abs(_getArea(eqn, y, secondIntersection) - _getArea(eqn, y, firstIntersection)) +
                   Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, secondIntersection));
        }

        // If not there is only one intersection
        // This one is when firstIntersection is in range
        if (firstIntersection >= x0){
            return Math.abs(_getArea(eqn, y, firstIntersection) - _getArea(eqn, y, x0)) +
                   Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, firstIntersection));
        }
        else {
            return Math.abs(_getArea(eqn, y, secondIntersection) - _getArea(eqn, y, x0)) +
                   Math.abs(_getArea(eqn, y, x1) - _getArea(eqn, y, secondIntersection));
        }
    }

    // Gets the area of the integral
    private double integrate(Equation eqn, int y, double x0, double x1){
        // Are we linear?
        if (eqn.a == 0){
            return _linearIntegral(eqn, y, x0, x1);
        }
        else {
            return _quadraticIntegral(eqn, y, x0, x1);
        }
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());

        for (int i = 0; i < n; ++i){
            String dlist[] = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int y = Integer.parseInt(dlist[1]);
            pointList.add(new Point(x, y));
        }

        // Add a sentinel point
        pointList.add(new Point(1<<30, pointList.get(n-1).y));

        int m = Integer.parseInt(r.readLine());

        for (int i = 0; i < m; ++i){
            String dlist[] = r.readLine().split(" ");
            int x = Integer.parseInt(dlist[0]);
            int a = Integer.parseInt(dlist[1]);
            int b = Integer.parseInt(dlist[2]);
            int c = Integer.parseInt(dlist[3]);
            eqnList.add(new Equation(x, a, b, c));
        }

        // Pointers to do sliding window
        int point = 0;
        int equation = 0;
        double prev = 0;
        double curr = 0;
        double out = 0;

        // Ok cool do integration
        while(point < n && equation < m){
            if (pointList.get(point).x < eqnList.get(equation).x){
                curr = pointList.get(point).x;
                out += integrate(eqnList.get(equation), pointList.get(point).y, prev, curr);
                point++;
            }
            else {
                curr = eqnList.get(equation).x;
                out += integrate(eqnList.get(equation), pointList.get(point).y, prev, curr);
                equation++;
            }

            // Then scoot the next bit over...
            prev = curr;
        }

        System.out.println(out);
    }

    public static void main(String[] args) throws IOException{
        PitchPerformance performance = new PitchPerformance();
        performance.run();
    }
}

