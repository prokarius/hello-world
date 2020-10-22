#include<stdio.h>

int attacks[1<<19];
int numAttackers[1<<19];

int ded[1<<19];
int toDelete[1<<19]; // Stack to see who can be deleted
int toDeleteHead = 0;

void push(int x){
    toDelete[toDeleteHead] = x;
    toDeleteHead++;
}

int pop(){
    toDeleteHead--;
    return toDelete[toDeleteHead];
}

int isEmpty(){
    return toDeleteHead == 0;
}

// Returns the length of a cycle
int cycleLen(int start){
    int len = 1;
    int curr = attacks[start];

    while (curr != start){
        len++;
        ded[curr] = 1;
        curr = attacks[curr];
    }
    ded[start] = 1;

    return len;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int x;
        scanf("%d", &x);
        x--;  // Who uses 1 index >:(
        attacks[i] = x;
        numAttackers[x]++;
    }

    // Go through the list, see who doesn't have any attackers
    for (int i = 0; i < n; ++i){
        if (numAttackers[i] == 0){
            push(i);
        }
    }

    int out = 0;

    // For each of the people with no attackers, remove them since they are mafija.
    // Also remove the person he points to because he cannot be a mafija.
    while (isEmpty() == 0){
        int mafija = pop();
        int citizen = attacks[mafija];

        // Oh, but the guy might already be ded!
        if (ded[mafija]) continue;

        ded[mafija] = 1;
        out++;

        // We might be double counting if the citizen is already ded!
        if (ded[citizen]) continue;
        ded[citizen] = 1;

        int underAttack = attacks[citizen];

        // If the person the citizen is pointing to has no more person accusing him,
        // then he can be mafija
        numAttackers[underAttack]--;
        if (numAttackers[underAttack] == 0 && ded[underAttack] == 0){
            push(underAttack);
        }
    }

    // Cool now we need to find all the cycles, and add floor(n/2) the number of
    // people to the out list.
    for (int i = 0; i < n; ++i){
        if (ded[i]) continue;

        out += cycleLen(i) / 2;
    }

    // Print that shit
    printf("%d\n", out);

    return 0;
}

