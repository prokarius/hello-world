#include<stdio.h>

// Linked list!
int LinkedList[1<<19];

int getNext(int curr){
    return LinkedList[curr];
}

void popNext(int prev){
    LinkedList[prev] = LinkedList[LinkedList[prev]];
}

// Onion onion!
int Onion[1<<19];
int find(int x){
    if (Onion[x] != x){
        Onion[x] = find(Onion[x]);
    }
    return Onion[x];
}

// a -> b
void onion(int a, int b){
    int parentb = find(b);
    if (parentb == a) return;

    // a links to the parent of b
    Onion[a] = parentb;
}

// a -> b. Ensure b's parent is not a
int check(int a, int b){
    return find(b) == a;
}

int mentee[1<<19];
int mentor[1<<19];

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // Initialize my onion
    for (int i = 1; i <= n; ++i){
        Onion[i] = i;
    }

    // And my linked list
    for (int i = 0; i <= n; ++i){
        LinkedList[i] = i+1;
    }

    for (int i = 1; i < n; ++i){
        int x;
        scanf("%d", &x);

        // See if the guy already is someone's mentor
        if (mentee[x] == 0 && check(i, x) == 0){
            mentee[x] = i;
            mentor[i] = x;
            onion(i, x); // i -> x
            continue;
        }

        // Ok shit, the guy already is someone's mentor. Time to iterate
        int curr = 0;
        while (curr < n){
            int lowest = getNext(curr);

            // Is the next best guy taken?
            if (mentee[lowest] != 0){
                int tmp = curr;
                curr = lowest;
                popNext(tmp);
                continue;
            }

            // If I follow the chain of mentees do I reach myself?
            if (check(i, lowest)){
                curr = lowest;
                continue;
            }

            // OK we are fulfilled
            mentee[lowest] = i;
            mentor[i] = lowest;
            onion(i, lowest);

            // Pop the guy because we don't ever need to consider him anymore
            popNext(curr);
            break;
        }
    }

    // TBH it doesn't even matter what the last guy wants
    // int x;
    // scanf("%d", &x);
    for (int i = 1; i <= n; ++i){
        if (mentee[i] == 0){
            mentor[n] = i;
            break;
        }
    }

    // Print everyone's preference
    for (int i = 1; i <= n; ++i){
        printf("%d ", mentor[i]);
    }
    printf("\n");

    return 0;
}

