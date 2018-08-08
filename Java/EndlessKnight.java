import java.io.*;
import java.util.*;

// Class to encapsulate a coordinate
class Coordinate {
    // Cartesian Coordinates
    private int x;
    private int y;
    // Knights Move Coordinates
    private int a; // (1, 2) vector
    private int b; // (2, 1) vector
    // We also want to keep in mind whether the rock is valid
    private boolean valid;

    // Public Constructor that takes a cartesian coodinate
    // This will also transform the coordinate into the knight's move coordinate
    public Coordinate (int x, int y){
        this.x = x;
        this.y = y;

        // a + 2b = x, 2a + b = y
        // a = (2y - x)/3 b = (2x - y)/3
        this.a = 2*y - x;
        this.b = 2*x - y;

        // Now to see if the rock is valid, we check if a and b are divisible mod 3
        this.valid = !((this.a % 3 != 0) || (this.b % 3 != 0));

        // Then calculate the actual value of a and b
        this.a /= 3;
        this.b /= 3;

        // Now, if a rock is also at a negative coordinate, it means it will never
        // be able to be reached by the knight, so we can say that rock is invalid.
        this.valid = this.valid && (this.a >= 0 && this.b >= 0);
    }

    // Returns if the rock is in a valid coordinate after the transform
    public boolean isValid(){
        return this.valid;
    }

    // Check to see if the b value of this coordinate is lower than the b value of
    // the supplied other b coordinate.
    public boolean before (Coordinate other){
        return this.b <= other.b;
    }

    // Since we are going to sort the rocks, we want to define an after function:
    // This will then have the order of the rocks be sorted in terms of a, then b.
    public boolean after(Coordinate other){
        if (this.a != other.a){
            return this.a > other.a;
        }
        return this.b > other.b;
    }

    // Returns the number of ways to get from this coordinate to that coordinate
    public int getWays(Coordinate other){
        int da = other.a - this.a;
        int db = other.b - this.b;
        return EndlessKnight.choose(da + db, db);
    }
}

// Class to encapsulate a Rock
// Actually I don't even know why I have this class
// It's a useless wrapper class for idk what. Im stupid.
class Rock {
    private Coordinate location;

    // Public constructor for a rock
    public Rock(int x, int y){
        this.location = new Coordinate(x, y);
    }

    // One more overloaded constructor so that we can do a nice hack with the goal
    // This will help later during PIE
    public Rock(Coordinate coordinate){
        this.location = coordinate;
    }

    // We want to be able to sort the rocks, so we need an after function too.
    // But we can simply call the after function in the Coordinate class.
    public boolean after(Rock other){
        return this.location.after(other.location);
    }

    // This function is to see if a rock can reach another without backtracking
    public boolean before(Rock other){
        return this.location.before(other.location);
    }

    // Gets the number of ways to get from this rock to that rock.
    public int getWays(Rock other){
        return this.location.getWays(other.location);
    }

    public boolean isValid(){
        return this.location.isValid();
    }
}

public class EndlessKnight{
    // Memo table for factorial function
    static int[] fact = new int[10010];
    static int[] inv = new int[10010];

    // This will initialise all the factorial memoization table for fast choose.
    private static void setting(){
        fact[0] = 1;
        inv[0] = 1;
        int factorial = 1;
        for (int i = 1; i < 10007; ++i){
            factorial = (factorial * i) % 10007;
            fact[i] = factorial;

            // Now we need to make the inverse factorial memotable.
            inv[i] = modInverse(fact[i], 10007);
        }
    }

    // Ripped off geekforgeeks
    private static int modInverse(int a, int m) {
        int m0 = m;
        int y = 0, x = 1;

        while (a > 1) {
            // q is quotient
            int q = a / m;
            int t = m;

            // m is remainder now, process same as
            // Euclid's algo
            m = a % m;
            a = t;
            t = y;

            // Update y and x
            y = x - q * y;
            x = t;
        }

        // Make x positive
        if (x < 0)
            x += m0;

        return x;
    }

    // This calculates the actual choose function.
    private static int choosehelper(int n, int r){
        // First check if r > n. If so, return 0 immediately
        if (r > n) return 0;

        // If not pull the values from n and multiply them together
        int out = fact[n];
        out = (out * inv[r]) % 10007;
        out = (out * inv[n-r]) % 10007;

        return out;
    }

    // Fast choose. This is essentially Lucas' Theorem
    // Suppose m = m0 + m1*p + m2*p**2...
    // Also    n = n0 + n1*p + n2*p**2...
    // Then lucas thrm says mCn = m0Cn0 * m1Cn1 * ... (mod p)
    // One consequence is that if nk > mk for some k, then mCn = 0 (mod p)
    public static int choose(int n, int r){
        // First we decompose n and r into their base p representation
        // Note that in this problem, n and r < 100M, however delta d can be as much
        // as 200M
        // Since p = 10007 and p**2 < 200M, there will be 3 calls to the actual
        // choose helper function.
        int n0 = n % 10007;
        int n1 = n / 10007;
        int n2 = n1 / 10007;
        n1 %= 10007;
        int r0 = r % 10007;
        int r1 = r / 10007;
        int r2 = r1 / 10007;
        r1 %= 10007;

        int out = (choosehelper(n0, r0) * choosehelper(n1, r1)) % 10007;
        return (out * choosehelper(n2, r2)) % 10007;
    }

    // This does PIE on the input.
    // rocks is the array of Rocks
    // ways is the number of ways to get from the front to the end
    // numselected is the number of rocks we have selected.
    // n is the total number of rocks we have to consider.
    // The selection includes curr as one of the selected rocks.
    private int pie(Rock[] rocks, int ways, int curr, int numselected, int n){
        // Base case: When we have reached the end, check to see if we have
        // selected anything at all. Do add/subtract accordingly
        if (curr == n){
            if (numselected >= 1){
                if (numselected % 2 == 0){
                    return -ways;
                }
                else {
                    return ways;
                }
            }
        }

        // Else we need to recurse
        // Initialise the original sum to be 0
        int sum = 0;

        // For rock, check to see if the next rock is further down than it.
        // Remember we only sorted the rocks based on x position, so as we loop
        // through the rocks we might end up processing a rock that is further down.
        for (int i = curr+1; i <= n; ++i){
            if (rocks[curr].before(rocks[i])){
                sum = (sum +
                       pie(rocks, (ways * rocks[curr].getWays(rocks[i])) % 10007,
                           i, numselected + 1, n)) % 10007;
            }
        }

        // Finally, return the sum:
        return sum;
    }

    public void run(int testcase, BufferedReader r) throws IOException{
        // Scan in the goal location and the number of rocks.
        String[] dlist = r.readLine().split(" ");
        int H = Integer.parseInt(dlist[0]) - 1; // -1 because Google >:(
        int W = Integer.parseInt(dlist[1]) - 1; // Y U array index start at 1?!
        int R = Integer.parseInt(dlist[2]);

        // We want to find out our goal, so make a coordinate for that!
        Coordinate goal = new Coordinate(H, W);

        // Of course, if the goal is not at a valid coordinate, we can just give up
        // immediately and return
        if (!goal.isValid()){
            System.out.printf("Case #%d: 0\n", testcase);

            // Oh, but not before scanning in all the rocks
            // If we fail to do this, we will AIOOB
            for (int i = 0; i < R; ++i){
                r.readLine();
            }
            return;
        }

        Rock[] rocks = new Rock[R + 2];
        rocks[0] = new Rock(0, 0);
        int rockcount = 0;

        // Scan and process the rocks
        for (int i = 0; i < R; ++i){
            String[] rockstr = r.readLine().split(" ");
            int x = Integer.parseInt(rockstr[0]) - 1;
            int y = Integer.parseInt(rockstr[1]) - 1;
            Rock rock = new Rock(x, y);

            // We push the rock into the list only if the rock is valid
            // This will save us some processing time later.
            if (rock.isValid()){
                rocks[++rockcount] = rock;
            }
        }

        // Sort the rocks first tho, this will make PIE easier later
        // 10 rocks? BUBBLE SORT!

        for (int i = 0; i <= rockcount; ++i){
            for (int j = 0; j < rockcount - i; ++j){
                if (rocks[j].after(rocks[j+1])){
                    Rock temp = rocks[j+1];
                    rocks[j+1] = rocks[j];
                    rocks[j] = temp;
                }
            }
        }

        // Last bit of nice hack: To pretend the endgoal is a piece of cheese as
        // well. This will allow us to just include the number of ways to get to the
        // end goal from the very start:
        rocks[++rockcount] = new Rock(goal);

        // Now the magic is to use the principle of Inclusion Exclusion!
        int output = (pie(rocks, 1, 0, 0, rockcount) + 10007) % 10007;
        System.out.printf("Case #%d: %d\n", testcase, output);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        EndlessKnight solution = new EndlessKnight();

        // Since we will be using a lot of bullcrap many times in this problem, lets
        // just define a setting function that will get up and running all the
        // static bullcrap.
        EndlessKnight.setting();

        // Now we run all the testcases and the like.
        int testcases = Integer.parseInt(r.readLine());
        for (int i = 0; i < testcases; ++i){
            solution.run(i+1, r);
        }
    }
}
