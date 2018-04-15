class Fenwick{
    // Constructor for a fenwick tree
    long[] fenwick;
    int size = 0;
    public Fenwick(int n){
        fenwick = new long[n];
        this.size = 0;
    }

    private int LSOne(int i){
        return (i & -i);
    }

    public void update(int v, long add){
        while (v < this.size){
            fenwick[v] += add;
            v += LSOne(v);
        }
    }

    public long rsq(int end){
        long sum = 0;
        while (end > 0){
            sum += fenwick[end];
            end -= LSOne(end);
        }
        return sum;
    }

    public long rsq(int start, int end){
        return rsq(end) - rsq(start);
    }
}

public class Turbo{
    private static ArrayList<Integer> input = new ArrayList<>();

    public static void main(String[] args){
        // Scan in input
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        for (int i=0; i<n; ++i){
            input.add(s.nextInt());
        }

        



    }
}
