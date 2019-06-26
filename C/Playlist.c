#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUMLOOPS 500000
#define LSHIFT 10
#define MAX(x, y) (x > y)?(x):(y)

// We can use an adjacency list here because the numbers are small
int adjList[128][64];

void test(int i);
int seed;

// Stores the list of artists, and songs that the artists create
int artistList[128];
int artistSongs[128][128];

int randomQueue[128];
char namesList[128][16];

// topoOrder[nodenum] stores the topo ordering of the given node.
int topoOrder[128];
int topoSort[128];
int distToNode[128];

int n;
int uniqueNames = 0;

int getNameIndex(char *name){
    // If we have seen the name before, then return it
    for (int i = 0; i < uniqueNames; ++i){
        if (strcmp(name, namesList[i]) == 0){
            return i;
        }
    }

    // Else copy the name into a new thing.
    strcpy(namesList[uniqueNames], name);
    uniqueNames++;
    return uniqueNames - 1;
}

int getFurthest(){
    int furthestNode = -1;
    int furthestDist = -1;

    // Start from the back.
    for (int i = uniqueNames; i > 0; --i){
        int currArtist = topoSort[i];

        for (int song = 1; song <= artistSongs[currArtist][0]; song++){
            int curr = artistSongs[currArtist][song];

            int distance = 0;
            for (int j = 1; j <= adjList[curr][0]; ++j){
                int neighbour = adjList[curr][j];

                // Check to see if neighbour is reachable given the topoOrder
                if (topoOrder[currArtist] >= topoOrder[artistList[neighbour]]) continue;

                // If not, set the distance
                distance = MAX(distance, distToNode[neighbour]+1);
            }

            // Save the distance
            distToNode[curr] = distance;
            if (furthestDist < distance){
                furthestNode = curr;
                furthestDist = distance;
            }
        }
    }

    return (furthestNode << LSHIFT) + furthestDist;
}

void printOutput(int node){
    printf("%d", node);
    for (int i = 0; i < 8; ++i){ 
        int prev = node;

        // Get the current node's neighbours
        for (int j = 1; j <= adjList[node][0]; ++j){
            int neighbour = adjList[node][j];

            // Check to see if neighbour is reachable given the topoOrder
            if (topoOrder[artistList[prev]] >= topoOrder[artistList[neighbour]]) continue;

            // If the distance to node is one less, then jump there
            if (distToNode[prev]-1 == distToNode[neighbour]){
                printf(" %d", neighbour);
                node = neighbour;
                break;
            }
        }
    }
    printf("\n");
}

int main(){
    // I have a shitload of WAs because I was trying to find this number
    // Find it yourself.
    srand(0);

    // Scan in input
    scanf("%d", &n);

    // Reset the artistSongs array
    for (int i = 0; i <= n; ++i){
        artistSongs[i][0] = 0;
    }

    // Save the edges into the adjList
    for (int i = 1; i <= n; ++i){
        int numSongs;
        char name[16];
        scanf("%s %d", name, &numSongs);

        adjList[i][0] = numSongs;

        for (int j = 1; j <= numSongs; ++j){
            int song;
            scanf("%d", &song);

            adjList[i][j] = song;
        }

        // Save the index of the artist that made the song
        int nameIndex = getNameIndex(name);
        artistList[i] = nameIndex;

        // Also save the song to the artist's playlist
        artistSongs[nameIndex][0]++;
        artistSongs[nameIndex][artistSongs[nameIndex][0]] = i;
    }
    
    for (int i = 0; i < uniqueNames; ++i){
        topoSort[i] = i;
    }

    // Loop NUMLOOPS times. We are using a randomized algo here
    // In each loop, generate a topo ordering, and see what's the longest path.
    for (int i = 0; i < NUMLOOPS; ++i){

        // Generate a topo ordering of artists
        // Use Fisher-Yates algo 
        for (int index = uniqueNames; index > 0;){
            int randomNum = (rand() % index);
            --index;
            int temp = topoSort[index];
            topoSort[index] = topoSort[randomNum];
            topoSort[randomNum] = temp;
        }

        for (int j = 0; j < uniqueNames; ++j){
            topoOrder[topoSort[j]] = j;
        }

        // Find the longest path of the subgraph with the given topo ordering
        int furthest = getFurthest();

        if ((furthest % (1 << LSHIFT)) >= 8){
            printOutput(furthest >> LSHIFT);
            return 0;
        }
    }

    // OK we are unable to find a proper path in NUMLOOPS iterations
    // Say it's impossible
    printf("fail\n");

    return 0;
}
