import java.util.Scanner;

public class Rings{
    public static void main(String[] arg){
        // Scan input
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        while (n != -1){
            Onion size = new Onion(n);
            Ring[] ringarr = new Ring[n];

            for (int i = 0; i<n; ++i){
                double x = s.nextDouble();
                double y = s.nextDouble();
                double z = s.nextDouble();
                ringarr[i] = new Ring(z, x, y);
            }

            for (int i = 0; i<n-1; ++i){
                for (int j = i+1; j<n; ++j){
                    if (Ring.overlap(ringarr[i], ringarr[j])) size.union(i, j);
                }
            }

            int best = 0;
            for (int i = 0; i<n; ++i){
                best = Math.max(size.size[i], best);
            }

            System.out.printf("The largest component contains %d ring", best);
            if (best == 1) System.out.printf(".\n");
            else System.out.printf ("s.\n");

            n = s.nextInt();
        }
    }

    // Ring Object
    static class Ring {
        // Properties
        double r;
        double x;
        double y;

        // Constructor
        public Ring(double r, double x, double y){
            this.r = r;
            this.x = x;
            this.y = y;
        }

        // Method to return if rings overlaps
        public static boolean overlap(Ring a, Ring b){
            double d = Math.hypot(a.x - b.x, a.y - b.y);
            // First one checks if the rings are close enough
            // Second one checks if the rings are not inside each other
            return d < (a.r + b.r) && d + Math.min(a.r, b.r) > Math.max(a.r, b.r);
        }
    }

    static class Onion{
        int[] parent;
        int[] size;

        public Onion(int n){
            parent = new int[n];
            size = new int[n];
            for (int i = 0; i<n; ++i){
                parent[i] = i;
                size[i] = 1;
            }
        }

        public int find (int i){
            if (parent[i] != i){
                parent[i] = find(parent[i]);
            }
            return parent[i];
        }

        public void union (int i, int j){
            int a = find(i);
            int b = find(j);
            if (a != b){
                parent[a] = b;
                size[b] += size[a];
            }
        }
    }
}
