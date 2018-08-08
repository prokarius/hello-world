// For more info, refer to UltraQuickSort's solution in the C folder

import java.io.*;
import java.util.*;

public class FroshWeek{
    int[] array;
    int[] temp;

    public long mergesort (int[] arr, int[] temp, int lo, int hi){
        long out = 0;
        if (lo < hi){
            int mid = lo + (hi - lo)/2;
            out += mergesort(arr, temp, lo, mid);
            out += mergesort(arr, temp, mid+1, hi);

            out += merge (arr, temp, lo, mid+1, hi);
        }
        return out;
    }

    public long merge (int[] arr, int[] temp, int lo, int mid, int hi){
        int i = lo;
        int j = mid;
        int k = lo;

        long count = 0;

        while ((i < mid) && (j <= hi)){
            if (arr[i] < arr[j]){
                temp[k++] = arr[i++];
            }
            else {
                temp[k++] = arr[j++];
                count += (mid - i);
            }
        }

        while (i < mid){
            temp[k++] = arr[i++];
        }
        while (j <= hi){
            temp[k++] = arr[j++];
        }

        for (int n = lo; n <= hi; ++n){
            arr[n] = temp[n];
        }

        return count;
    }

    public void run(int n, BufferedReader r) throws IOException{
        array = new int[n];
        temp = new int[n];
        for (int i = 0; i < n; ++i){
            int next = Integer.parseInt(r.readLine());
            array[i] = next;
        }

        System.out.println(mergesort(array, temp, 0, n-1));
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        FroshWeek froshweek = new FroshWeek();
        froshweek.run(n, r);
    }
}
