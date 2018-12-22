#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) (x>y)?(x):(y)

// ... I have imaginative names yes
typedef struct {
    int number;
    int a;
    int b;
} Number;

// Yes, a 16M big array of Numbers!
Number numbers[16000005];
int num = 0;
int input[4005];

// Unintentionally obfuscating my code with shitty naming.
// Sorry. I don't mean to. <-- lies.
void push(Number number){
    numbers[num++] = number;
}

// So that we can sort later.
int cmpfunc(const void* a, const void* b){
    Number first = *(Number*) a;
    Number second = *(Number*) b;
    return first.number - second.number;
}

int binSearch(int target){
    int lo = 0;
    int hi = num;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        // Check if x is present at mid
        if (numbers[mid].number == target){
            return mid;
        }
        // If x greater, ignore left half
        if (numbers[mid].number < target){
            lo = mid + 1;
        }
        // If x is smaller, ignore right half
        else{
            hi = mid - 1;
        }
    }

    // Well, just return 1. We'll hit the sentinel values or something whatever.
    return 1;
}

int main(){
    // Scan in input
    int n;
    scanf ("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &input[i]);
    }

    // We are going to enumerate all possible numbers and push them into the list.
    for (short i = 0; i < n-1; ++i){
        for (short j = i+1; j < n; ++j){
            Number new;
            new.number = input[i] + input[j];
            new.a = i;
            new.b = j;
            push(new);
        }
    }

    // Push sentinel values into the array
    Number sentinel = {1800000000, 0, 0};
    push (sentinel);
    push (sentinel);
    Number sentinel2 = {-1800000000, 0, 0};
    push (sentinel2);

    // sort the list!
    qsort(numbers, num, sizeof(Number), cmpfunc);

    int best = 1<<31; // -INF;

    // For each possible d - c, we do binsearch to find corresponding a + b
    for (short i = 0; i < n; ++i){
        for (short j = 0; j < n; ++j){
            if (i == j) continue;
            int target = input[i] - input[j];
            int loc = binSearch(target);

            // Then scoot upwards and downwards and ensure a b c d are distinct
            int upper = loc;
            int lower = loc + 1;
            while (numbers[upper].number == target){
                if (i != numbers[upper].a &&
                    i != numbers[upper].b &&
                    j != numbers[upper].a &&
                    j != numbers[upper].b){

                    // Yes, we have found such a pair
                    best = MAX(best, target + input[j]);
                    break;
                }
                else {
                    upper++;
                }
            }

            // Repeat for lower boundary too
            while (numbers[lower].number == target){
                if (i != numbers[lower].a &&
                    i != numbers[lower].b &&
                    j != numbers[lower].a &&
                    j != numbers[lower].b){

                    // Yes, we have found such a pair
                    best = MAX(best, target + input[j]);
                    break;
                }
                else {
                    lower--;
                }
            }
        }
    }

    // Check if we did find a match, and print
    if (best == 1<<31){
        printf("no solution\n");
    }
    else {
        printf("%d\n", best);
    }
    return 0;
}
