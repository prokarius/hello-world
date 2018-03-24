import java.util.*;

// Encapsulates the idea behind an element of the input array
class Element{
    private long below;
    private long above;
    private int number;

    // Constructor. Creates a new Element.
    // Sets the number of elements that's out of order to be zero.
    public Element(int number){
        this.number = number;
        this.above = 0;
        this.below = 0;
    }

    // Getter function to get the number of elements above it that isn't in order
    // Preconditions: None
    // Postconditions: Returns number of elements above it that is out of order
    public long getAbove(){
        return this.above;
    }

    // Getter function to get the number of elements below it that isn't in order
    // Preconditions: None
    // Postconditions: Returns number of elements below it that is out of order
    public long getBelow(){
        return this.below;
    }

    // Updates the number of elements below it that's out of order
    // Preconditions: none
    // Postconditions: Element has an updated below property
    public void setBelow(int number){
        this.below += number;
    }

    // Updates the number of elements above it that's out of order
    // Preconditions: none
    // Postconditions: Element has an updated above property
    public void setAbove(int number){
        this.above += number;
    }

    // Method to return the number of mega inversions with this element as the
    // 2nd element.
    // Preconditions: None
    // Postconditions: Returns the number of mega inversions.
    public long megaInv(){
        return this.above * this.below;
    }

    // Compares if the current element is larger than the given other Element e.
    // Returns +1 if the current element is strictly larger than e
    // Returns  0 if the current element is equal to e.
    // Returns -1 if the current element is strictly smaller than e
    // Preconditions: None
    // Postconditions: Returns an int according to the above
    public int compare(Element e){
        if (this.number > e.number){
            return 1;
        }
        else if (this.number < e.number){
            return -1;
        }
        else {
            return 0;
        }
    }
}

// Main class
public class MegaInversion{
    // Create the original list of elements
    static ArrayList<Element> input = new ArrayList<>();

    public static void main(String[] args){
        // Scan in our input, and push into new list
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        for (int i=0; i<n; ++i){
            int value = s.nextInt();
            input.add(new Element(value));
        }

        ArrayList<Element> temporary = new ArrayList<>();

        for (int i=0; i<n; ++i){
            temporary.add(new Element(-1));
        }

        // Then run a merge operation on the entire list
        mergesort(input, temporary, 0, input.size());

        // Then sum up the output:
        long output = 0;
        for (Element e : input){
            output += e.megaInv();
        }

        // Then print the output
        System.out.println(output);
    }

    // Does a mergesort operation on arr
    // This is a recursive algorithm
    // Precondition: arr in the main class is populated with elements to sort
    // Precondition: left and right are bounds within the array.
    // Postcondition: arr is now sorted
    // Postcondition: each element e in arr has the correct number of elements
    // that are out of order below and above it.
    public static void mergesort(ArrayList<Element> arr, ArrayList<Element> temp, int left, int right){
        // Base case is when left >= right
        if (left >= right - 1){
            return;
        }

        // Else, recurse
        int mid = left + (right - left)/2;
        mergesort(arr, temp, left, mid);
        mergesort(arr, temp, mid, right);
        merge (arr, temp, left, mid, right);
    }

    // Merges the two input ArrayLists together.
    // At the same time, update the number of out of order elements
    // Precondition: list1 and list2 are already in sorted order
    // Postcondition: returns a new list where list1 and list2 have been merged
    public static void merge(ArrayList<Element> arr, ArrayList<Element> temp, int left, int mid, int right){
        // Copy over the elements from arr to temp in the range [left, right)
        for (int i=left; i<right; ++i){
            temp.set(i, arr.get(i));
        }

        int i = left;
        int j = mid;
        int k = left;

        // While we have stuff to push into the original list
        // We push it into the original list
        // Now we also need to remember to update the number of
        while ((i < mid) && (j < right)){
            Element e1 = temp.get(i);
            Element e2 = temp.get(j);

            // If list1 < list2, then
            // Set the number of elements above it that is not in order
            // Else do the same thing for the other way round.
            if (e1.compare(e2) <= 0){
                e1.setAbove(j - mid);
                arr.set(k, e1);
                ++i;
            }
            else {
                e2.setBelow(mid - i);
                arr.set(k, e2);
                ++j;
            }

            // Increase the counter where we push
            ++k;
        }

        // Now, push whatever is remaining into the big list
        while (i < mid){
            Element e = temp.get(i);
            e.setAbove(right - mid);
            arr.set(k, e);
            ++i;
            ++k;
        }
    }
}

