import java.util.*;
import java.io.*;

public class FroshWeek{
    public long mergesort(int[] arr, int[] temp, int lo, int hi){
        long total = 0;
        if (lo < hi){
            int mid = (lo + hi) / 2;
            total += mergesort(arr, temp, lo, mid);
            total += mergesort(arr, temp, mid + 1, hi);

            total += merge (arr, temp, lo, mid+1, hi);
        }

        return total;
    }

    public long merge(int[] arr, int[] temp, int lo, int mid, int hi){
        int i = lo;
        int j = mid;
        int k = lo;

        long out = 0;

        while ((i < mid) && (j <= hi)){
            if (arr[i] < arr[j]){
                temp[k] = arr[i];
                k++;
                i++;
            }
            else {
                temp[k] = arr[j];
                k++;
                j++;
                out += mid - i;
            }
        }

        while(i < mid){
            temp[k] = arr[i];
            k++;
            i++;
        }

        while (j <= hi){
            temp[k] = arr[j];
            k++;
            j++;
        }

        for (int r = lo; r <= hi; ++r){
            arr[r] = temp[r];
        }

        return out;
    }

    public void run() throws IOException{
        // Creating our stuff
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        int[] array = new int[n];
        int[] temp = new int[n];

        for (int i = 0; i < n; ++i){
            int next = Integer.parseInt(r.readLine());
            array[i] = next;
        }

        // Printing our result
        System.out.println(mergesort(array, temp, 0, n-1));
    }

    public static void main(String[] args) throws IOException{
        FroshWeek froshweek = new FroshWeek();
        froshweek.run();
    }
}

