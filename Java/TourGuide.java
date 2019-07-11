import java.io.*;
import java.util.*;

class Person{
    double startPosX;
    double startPosY;
    double currPosX;
    double currPosY;
    double speed;
    double direction;
    double timeOfReturn;

    public Person(double x, double y, double v, double theta){
        this.startPosX = x;
        this.startPosY = y;
        this.speed = v;
        this.direction = theta;
    }

    public void setPos(double t){
        this.currPosX = this.startPosX + t * this.speed * Math.cos(this.direction);
        this.currPosY = this.startPosY + t * this.speed * Math.sin(this.direction);
    }

    // Returns the position
    public double getPosX(){
        return this.currPosX;
    }

    public double getPosY(){
        return this.currPosY;
    }

    // When can I intersect this dude? Returns the time it takes
    // Also update the timeOfReturn
    public double getIntersection(double myX, double myY, double mySpeed, double time){
        double dx = this.currPosX - myX;
        double dy = this.currPosY - myY;

        // The equation is (dx + vxt)**2 + (dy + vyt)**2 = (mySpeed*t)**2
        // => dx**2 + dy**2 + 2(dxvx + dyvy)t + (speed ** 2)t**2 = mySpeed**2 t**2
        // => (speed**2 - mySpeed**2) t**2 + 2(dxvx + dyvy) t + distance**2 = 0

        // Solve the quadratic equation
        // There will always be a solution
        double a = this.speed*this.speed - mySpeed*mySpeed;
        double b = 2 * this.speed * (dx * Math.cos(this.direction) +
                                     dy * Math.sin(this.direction));
        double c = dx*dx + dy*dy;

        double t = (-b - Math.sqrt(b*b - 4*a*c)) / (2*a);

        this.currPosX = this.currPosX + t * this.speed * Math.cos(this.direction);
        this.currPosY = this.currPosY + t * this.speed * Math.sin(this.direction);

        this.timeOfReturn = t + time + this.returnToOrigin();

        return t;
    }

    // How long does the dude take to get back to the origin?
    private double returnToOrigin(){
        double distance = Math.sqrt(this.currPosX*this.currPosX + this.currPosY*this.currPosY);
        return distance / this.speed;
    }
}


public class TourGuide{
    int n;
    Person[] persons;
    boolean[] visited;

    double mySpeed;
    double best = 100000007;

    public TourGuide(int n){
        this.n = n;
        this.persons = new Person[n];
        this.visited = new boolean[n];
    }

    // Gets the best distance
    private void recurse(int lastPerson, int numRescued, double myX, double myY, double time){
        if (numRescued == this.n){
            double slowest = -1;
            for (int i = 0; i < this.n; ++i){
                slowest = Math.max(slowest, persons[i].timeOfReturn);
            }

            best = Math.min(best, slowest);
            return;
        }

        for (int i = 0; i < this.n; ++i){
            if (visited[i]) continue;
            visited[i] = true;

            // Find out where he is at the given time
            persons[i].setPos(time);

            // Find the time it takes to intersect him
            double timeTaken = persons[i].getIntersection(myX, myY, mySpeed, time);

            // Then recurse
            // But prune first
            if (time + timeTaken < best){
                double newX = persons[i].getPosX();
                double newY = persons[i].getPosY();

                recurse(i, numRescued + 1, newX, newY, time + timeTaken);
            }
            visited[i] = false;
        }
    }

    private void run(BufferedReader r) throws IOException{

        // Scan in input
        mySpeed = Double.parseDouble(r.readLine());

        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            persons[i] = new Person(Double.parseDouble(dlist[0]), Double.parseDouble(dlist[1]),
                                    Double.parseDouble(dlist[2]), Double.parseDouble(dlist[3]));
        }

        // Then do recursion
        recurse(0, 0, 0, 0, 0);

        // Last, print out the best time
        System.out.println(Math.round(best));
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 

        int n = Integer.parseInt(r.readLine());
        while (n != 0){
            TourGuide tourguide = new TourGuide(n);
            tourguide.run(r);
            n = Integer.parseInt(r.readLine());
        }
    }
}
