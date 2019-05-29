import java.io.*;
import java.util.*;

class Point {
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

    // We want to order it from highest to lowest
    public int compareTo(Point other){
        if (this.y == other.y){
            return this.x - other.x;
        }
        return this.y - other.y;
    }
}

class Line implements Comparable<Line> {
    private Point start;
    private Point end;

    public Line (Point a, Point b){
        if (a.compareTo(b) > 0){
            this.start = a;
            this.end = b;
        }
        else {
            this.start = b;
            this.end = a;
        }
    }

    // Given y, evaluate the x value where the line cuts the given y coordinate
    // Assumption is that 
    public double eval(double y){
        double dy = this.end.getY() - this.start.getY();
        double dx = this.end.getX() - this.start.getX();

        return ((y - this.start.getY()) * dx / dy) + this.start.getX();
    }

    public Point getStart(){
        return this.start;
    }

    public Point getEnd(){
        return this.end;
    }


    public int compareTo(Line other){
        if (this.start.getY() == other.start.getY()){
            return (this.end.getY() < other.end.getY())?(-1):(1);
        }
        return (this.start.getY() < other.start.getY())?(-1):(1);
    }
}

public class Pinball{
    PriorityQueue<Line> eventQueue = new PriorityQueue<>();
    TreeSet<Line> active = new TreeSet<>();

    private void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        // Scan in input
        int n = Integer.parseInt(r.readLine());

        // For each line, scan in input
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");

        }
    }

    public static void main(String[] args) throws IOException{
        Pinball pinball = new Pinball();
        pinball.run();
    }
}
