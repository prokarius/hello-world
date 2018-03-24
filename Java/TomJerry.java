import java.util.*;

public class TomJerry {
    // Some next level nested class shit going on here bro
    public static class Cheese {
        private int x;
        private int y;

        public Cheese (int a, int b){
            x = a;
            y = b;
        }

        // Returns true if cheese next is after this cheese
        // Will use this during the sorting by x, then y
        // Assumes that x and y are distinct
        public boolean after(Cheese next){
            if (this.x != next.x)
                return this.x < next.x;
            else
                return this.y < next.y;
        }

        // Returns true if this cheese can go to next cheese
        public boolean displacement (Cheese next){
            return next.y >= this.y;
        }

        // Getter functions
        public int getx (Cheese next){
            return next.x - this.x;
        }

        public int gety (Cheese next){
            return next.y - this.y;
        }
    }


    final static long MOD = 1000000007;
    static long[] fact = new long[100005];
    static long[] inv = new long[100005];
    static Cheese[] arr = new Cheese[11];
    static long out = 0;
    static int[] negative = {1, -1};

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int w = s.nextInt();
        int h = s.nextInt();
        setting (w+h);

        // Set the first cheese to be the start point:
        arr[0] = new Cheese (1,1);

        // Scan in the cheese, but if n is 0, just break;
        int n = s.nextInt();
        if (n == 0){
            System.out.println("0");
            System.exit(0);
        }

        for (int i=1; i<=n; ++i){
            int x = s.nextInt();
            int y = s.nextInt();
            arr[i] = new Cheese(x, y);
        }

        // Sort arr by x then y.
        // Don't bother with fancy shit like quick. Bubble!
        Arrays.sort(arr, 0, n+1, (cheese1, cheese2) -> cheese1.after(cheese2) ? -1 : 1);

        
        // for (int i=0; i<=n; ++i){
        //     for (int j=0; j<n; ++j){
        //         if (!arr[j].after(arr[j+1])){
        //             Cheese temp = arr[j+1];
        //             arr[j+1] = arr[j];
        //             arr[j] = temp;
        //         }
        //     }
        // }

        // Nice hack, by pretending the end node is a piece of cheese too
        arr[++n] = new Cheese(w, h);

        // Do PIE here.
        System.out.println((pie(arr, 1, 0, 0, n)+MOD) % MOD);
    }

    private static long pie (Cheese[] arr, long ways, int curr, int numselect, int n){
        // Recursively does PIE on the stuff
        // Selection includes curr
        // Base cases:
        // When current cheese is the catapult cheese and we have at least 1 cheese
        if (curr == n){
            if (numselect > 1) return negative[numselect%2]*ways;
            else return 0;
        }

        // For each of the pieces of cheese,
        // If you cannot reach a piece of cheese, add 0
        long sum = 0;
        for (int i=curr+1; i<=n; ++i){
            if (arr[curr].displacement(arr[i])){
                int dy = arr[curr].gety(arr[i]);
                int dx = arr[curr].getx(arr[i]);
                sum = (sum + pie(arr, (ways*choose(dy+dx, dx)) % MOD, i, numselect+1, n)) % MOD;
            }
        }
        return sum % MOD;
    }

    // Function to set up shit
    private static void setting (int n){
        fact[0] = 1;
        inv[0] = 1;
        for (int i=1; i<n+1; ++i){
            fact[i] = i*fact[i-1] % MOD;
            inv[i] = inverse(fact[i], MOD) % MOD;
        }
    }

    // Function to calculate inverse of n!
    // Ripped off geekforgeeks
    private static long inverse (long a, long m){
        long m0 = m;
        long y = 0, x = 1;

        while (a > 1){
            long q = a/m;
            long t = m;
            m = a%m;
            a = t;
            t = y;

            y = x - q*y;
            x = t;
        }

        if (x < 0) x += m0;
        return x;
    }

    // Returns nCr
    private static long choose (int N, int R){
        long temp = (fact[N] * inv[R])%MOD;
        return (temp * inv[N-R])%MOD;
    }
}
