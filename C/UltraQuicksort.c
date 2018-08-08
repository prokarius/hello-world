#include<stdio.h>

int array[500005]; // Input array
int temp[500005];  // Temporary array. Used for mergesort

// Merge step. The counting and magic happens here
long long merge(int arr[], int temp[], int lo, int mid, int hi){
    int i = lo;  // Index for left subarray
    int j = mid; // Index for right subarray
    int k = lo;  // Index for resulting merged subarray
    long long count = 0;

    // While we have not reached the end of the two arrays yet
    // Check if the current elements are in the right order.
    while ((i <= mid - 1) && (j <= hi)){
        // If they are in the right order, just copy the guy over
        if (arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        }
        // Else copy the guy in the right sive over
        // Also add the number of elements that have yet to be processed
        // This is because since the two subarrays have been sorted already
        // The number of elements that are larger than the out of order element
        // is equal to the number of elements left in the unsorted list
        else {
            temp[k++] = arr[j++];
            count += (mid - i);
        }
    }

    // Copy the remaining elements of the left array, then the right array.
    while (i < mid){
        temp[k++] = arr[i++];
    }
    while (j <= hi){
        temp[k++] = arr[j++];
    }

    // Copy the temp array back into the original array
    for (int i = lo; i <= hi; ++i){
        arr[i] = temp[i];
    }

    // Return the count
    return count;
}

// Mergesort function
// This is where the recursion occurs
long long mergesort(int arr[], int temp[], int lo, int hi){
    long long out = 0;
    if (lo < hi){
        // Get the mid point and call recursive merge.
        // Remember to add the number of inversions to the output.
        int mid = (lo + (hi - lo)/2);
        out += mergesort(arr, temp, lo, mid);
        out += mergesort(arr, temp, mid+1, hi);

        // Then call the merge step and add the number of inversions to output.
        out += merge(arr, temp, lo, mid+1, hi);
    }

    // Finally return output
    return out;
}


int main(){
    // Scan in our shit
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d", &array[i]);
    }

    // Do mergesort
    printf ("%lld\n", mergesort(array, temp, 0, n-1));
    return 0;
}
