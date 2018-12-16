#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* VARIABLES RELATED TO THE GENERATION OF ADJMATRIX */

// This is the word list of the input dictionary.
char wordlist[25200][17];

// This array holds the indices to the words.
// We will do the sorting operations on this array.
int wordindex[25200];

// Ghetto adjacency list.
// Assuming the wordlist is completely made of English lowercase words.
// A string can have up to 16 * 26 = 416 outgoing edges.
// Note that the first index of each would be the number of outgoing edges.
int adjmatrix[25200][425];

// Make the character of comparison a global variable, so that cmpfunc has access to it.
// Also make the number of input words into a global too.
int charOfCmp;
int n = 0;


/* VARIABLES RELATED TO BFS STUFF FOR PART 2 OF THE QUESTION*/

// ghettoQueue for BFS later down the line.
// BFS ghettoQueue functions here also!
int visited[25200];
int ghettoQueue[100000];
int ghettoQueueHead = 0;
int ghettoQueueTail = 0;

void push(int value){
    ghettoQueue[ghettoQueueHead++] = value;
}

int pop(){
    int output = ghettoQueue[ghettoQueueTail];
    ghettoQueueTail++;
    return output;
}

int bfsSize(){
    return ghettoQueueHead - ghettoQueueTail;
}

void resetQueue(){
    ghettoQueueHead = 0;
    ghettoQueueTail = 0;
}

void resetVisited(){
    for (int i = 0; i < n; ++i){
        visited[i] = 1<<21;
    }
}


/* ACTUAL ALGORITHM AND IMPLEMENTATION OF THE CODE */

// The meat of the code. This is where the magic happens.
// We will replace the character we are considering with a dummy character.
// Then suppose that character is the only one changed, then strcmp will return 0.
int cmpfunc(const void* a, const void* b){
    int first = *(int *)a;
    int second = *(int *)b;

    // Save the characters from the words in the word list.
    // This is so that we can regenerate them later.
    char savedFromA = wordlist[first][charOfCmp];
    char savedFromB = wordlist[second][charOfCmp];

    // Replace the characters at the index with some character that will not appear.
    // NOTE FROM THE FUTURE: THIS IS NAIVE!
    // What if the two words are: "scar" and "scare"?
    // Then when we are comparing index 4, and simply replace the letters, we will draw
    // a link between "scar" and "scare"!
    // We need to check to make sure we are not replacing characters outside words!

    // The simplest way is just to make sure that what we saved from A or B is not the
    // null character. If it is, we know that the word has already ended.
    if (savedFromA) wordlist[first][charOfCmp] = '=';
    if (savedFromB) wordlist[second][charOfCmp] = '=';

    // Now we can call strcmp on the two words.
    // The return value of strcmp will be the return value of our cmpfunc.
    // Note that this will mean words that have only that one character changed
    // will be next to each other after the qsort, even if not lexicographical.
    int output = strcmp(wordlist[first], wordlist[second]);

    // Don't forget to regenerate the original words before returning output!
    wordlist[first][charOfCmp] = savedFromA;
    wordlist[second][charOfCmp] = savedFromB;

    return output;
}

// So much for proper software engineering and "Single Line of Abstraction Per method"
// or whatever that SLAP thing they teach in CS2103T is.
// I mean I'm mixing SLAP ideals with non SLAP ideals so... well...
int main(){
    while (1){
        // Note that we cannot use scanf here. scanf will just ignore the newline character.
        // GDI wasted 30 minutes thinking of how to solve this.
        // Sometimes simplicity is the best eh?
        gets(wordlist[n]);

        // We have reached the end of the input
        if (wordlist[n][0] == 0){
            break;
        }
        else {
            wordindex[n] = n;
            n++;
        }
    }

    // Here, n would be the number of words we have scanned in.
    // We want to initialise the adjmatrix here.
    // Recall that adjmatrix[0] will store the end of the adjlist.
    for (int i = 0; i < n; ++i){
        adjmatrix[i][0] = 1;
    }

    // Quickly create the adjlist of values
    // We can do this in O(n log n) by using quicksort.
    // However, we need a smart compare function as described above.
    for (charOfCmp = 0; charOfCmp < 16; ++charOfCmp){
        // But see, here's the thing, we don't want to sort the words themselves
        // Because scooting around 16 character = 64 bytes takes a long time.
        // I should have realised this bit sooner knowing that the cmpfunc simply
        // takes in pointers, so technically I can do magical casting
        qsort(wordindex, n, sizeof(int), cmpfunc);

        // Here, all the words are sorted regardless of the charOfCmp'th letter.
        // We need to find for each word who are his neighbours.
        for (int wordA = 0; wordA < n; ++wordA){
            for (int wordB = wordA + 1; wordB < n; ++wordB){

                // We simply need to use cmpfunc to check here.
                // Note that since cmpfunc takes in pointers to an index in wordlist,
                // we need to cast the position we are indexing as a pointer.
                if (cmpfunc(&wordindex[wordA], &wordindex[wordB]) != 0){
                    // Notice that if we cmpfunc is not 0, the only case is that
                    // wordB is not 1 away from wordA.
                    // And from then on, wordB will NEVER be 1 away from wordA.
                    // Hence we are allowed to break here!
                    break;
                }

                // If we are here, wordindex[wordA] and wordindex[wordB] are
                // connected by an edge! We can then populate the adjacency list.

                // Push the nodes into each other's adjacentcy list.
                adjmatrix[wordindex[wordA]][adjmatrix[wordindex[wordA]][0]] = wordindex[wordB];
                adjmatrix[wordindex[wordB]][adjmatrix[wordindex[wordB]][0]] = wordindex[wordA];

                // Add 1 to the number of elements as tracked.
                adjmatrix[wordindex[wordA]][0]++;
                adjmatrix[wordindex[wordB]][0]++;
            }
        }
    }

    // Yay! We have the adjacency list! Now we can do BFS~!
    // Repeat this for all the queries
    char wordFrom[20], wordTo[20];
    int from, to;
    int count = 0;
    while(scanf(" %s %s", wordFrom, wordTo) == 2){

        // Find out the to and from index
        for (from = 0;; from++){
            if (strcmp(wordFrom, wordlist[from]) == 0) break;
        }
        for (to = 0;; to++){
            if (strcmp(wordTo, wordlist[to]) == 0) break;
        }

        // Initialize the visited array.
        resetVisited();
        resetQueue();
        visited[to] = -1;

        // Do BFS
        push(to);
        while (bfsSize() > 0){
            int curr = pop();
            for (int i = 1; i < adjmatrix[curr][0]; ++i){
                int neighbour = adjmatrix[curr][i];
                if (visited[neighbour] < 1 << 20) continue;
                visited[neighbour] = curr;
                push(neighbour);

                // If we have reached the end, prematurely end the loop.
                if (neighbour == from){
                    resetQueue();
                    break;
                }
            }
        }

        // OK Last bit! We need to process the printing.
        // If this is not the first time we are doing this, print a new line character.
        if (count != 0) printf("\n");
        count++;

        // Now we have the BFS from the finish line, we can simply retrace the steps
        // backwards to print the words in order.
        if (visited[from] > 1<<20){
            printf("No solution.\n");
            continue;
        }
        int curr = from;
        while (curr != -1){
            printf("%s\n", wordlist[curr]);
            curr = visited[curr];
        }
    }
    return 0;
}