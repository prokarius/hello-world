import java.io.*;
import java.util.*;

class Point implements Comparable<Point>{
    long x;
    long y;

    public Point (long x, long y){
        this.x = x;
        this.y = y;
    }

    // We sort by comparing the y values first.
    // If not, then we compare x values.
    public int compareTo (Point other){
        if (this.y != other.y){
            return this.y - other.y;
        }
        return this.x - other.x;
    }
}


class Line implements Comparable<Line>{
    Point head;
    Point tail;

    // Public Constructor, head should always be less than tail.
    public Line (Point head, Point tail){
        this.head = head;
        this.tail = tail;
    }

    // Line comparator
    public int compareTo (Line other){

    }
}

public class Pinball{
    public void run() throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
    }

    public static void main(String[] args) throws IOException{
        Pinball pinball = new Pinball();
        pinball.run();
    }
}
