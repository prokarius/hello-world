import java.util.*;

public class FruitsBasket {
    static long[] arr = new long[42];
    static long[] sum = new long[42];
    static long[] two = new long[42];

    public static void setting(){
        two[0] = 1;
        for (int i=1; i< 40; ++i){
            two[i] = two[i-1]*2;
        }
    }

    public static void main(String[] args){
        setting();

        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        long out = 0;
        for (int i=0; i<n; ++i){
            int ph = s.nextInt();
            arr[i] = ph;
        }

        // Calculate the suffix sum
        sum[n] = arr[n];
        for (int i=n-1; i>=0; --i) sum[i] = sum[i+1] + arr[i];
        for (int i=0; i<n; ++i){System.out.println(sum[i]);}

        // For each fruit, recurse.
        for (int i=0; i<n; ++i){
            out += recurse (i, arr[i], n);
        }
        System.out.println(out);
    }

    private static long recurse(int last, long weight, int n){
        // Note that weight includes the weight of the "last" fruit
        // Terminating conditions:
        // When the last fruit is greater than n
        if (last == n-1){
            if (weight < 200) return 0;
            else return weight;
        }
        // If weight is greater than 200:
        if (weight >= 200) return two[n-last-2]*(sum[last+1]+2*weight);

        // Else we can sum up
        long ret = 0;
        for (int i=last+1; i<n; ++i) ret += recurse(i, weight + arr[i], n);
        return ret;
    }
}
