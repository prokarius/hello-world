#include<stdio.h>
#include<stdlib.h>
#define MIN(x,y) (x<y)?(x):(y)
#define MAX(x,y) (x>y)?(x):(y)

int maax=1, array[2505], onion[2505], ans[2505], size[2505], ans2[102];
long long edgelist[5005];

// Sort it in a decreasing order. i.e. highest edge first
int cmp(const void * a, const void * b){
    return ( *(long long*)b - *(long long*)a);
}

// Onion methods. Oniononion is slightly modified though.
int find(int a){
    if (onion[a] == a) return a;
    onion[a] = find(onion[a]);
    return onion[a];
}

// Note that the size of the onion matters. Do what we did in AlmostOnion!
void oniononion (int a, int b){
    int pa = find(a);
    int pb = find(b);
    if (pa == pb){return;}
    onion[pa] = pb;
    size[pb] += size[pa];
    maax = MAX(maax, size[pb]);
}

int main(){
    int i, j, r, c;
    // Scan in the data
    scanf ("%d %d" , &r, &c);
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            scanf("%d", &array[i*c+j]);
        }
    }

    // Consider the global maximum of the entire area to range from 0 to 99.
    // The edges between each plot of land will be the minimum of the two.
    // Label each edge as an ll: 9M*w + 3000*start + end
    // Start by considering rows, then go into columns.
    // Note that object macros are weird. When in doubt, put brackets.
    int edgep = -1;
    for (i=0; i<r; ++i){
        for (j=0; j<(c-1); ++j){
            edgelist[++edgep] = (MIN(array[i*c+j], array[i*c+j+1])) * 9000000 +
                                3000*(i*c+j) + i*c+j+1;
        }
    }
    for (i=0; i<(r-1); ++i){
        for (j=0; j<c; ++j){
            edgelist[++edgep] = (MIN(array[i*c+j], array[(i+1)*c+j])) * 9000000 +
                                3000*(i*c+j) + (i+1)*c+j;
        }
    }

    // Sort the list of edges
    qsort (edgelist, r*(c-1) + c*(r-1), sizeof(long long), cmp);

    // Add a terminator:
    edgelist[++edgep] = 1LL << 60;

    // Now, we pretend that the world only has plots of land less than globalmax
    // Then we loop through the list and when we can, onion.
    // We also need to keep track of the largest plot of land
    int globalmax = 100, currmin;

    // Before we do the onion, we need to set the size up:
    for (i = 0; i < r*c; ++i) size[i] = 1;

    // Precompute the onion. So we are going to do a bunch of onions.
    // We fix globalmax to go from 0 to 100.
    // Find the max by simply storing the best at each onion.
    // We can do that by applying the AlmostOnion style algo.
    int w, x ,y;
    long long curredge;
    while (globalmax > -1){
        currmin = globalmax;
        edgep = 0;
        w = 1000;

        // Bring edgep to the start point by iterating through and checking.
        while (w > globalmax){
            curredge = edgelist[edgep++];
            w = curredge/9000000;
        }
        --edgep;

        // Now we are at the correct start point. Pull an edge and check weight.
        // If it's greater than currmin, oniononion it
        // Else, see what the current max plot is, save that as the max plot
        // size with height difference globalmax-currmin. (This is ans2).
        while (currmin > -1 && edgep < (r-1)*c + (c-1)*r){
            curredge = edgelist[edgep];
            w = curredge/9000000;

            // But then again, remember that we have to check if the heights of
            // the two plots of land are indeed <= globalmax
            // Cuz if they are not, then we are not allowed to oniononion them.
            if (w >= currmin){
                x = curredge%3000;
                y = (curredge/3000)%3000;
                ++edgep;
                if (array[x] > globalmax || array[y] > globalmax) continue;
                oniononion(x, y);
            }

            // Else we have
            else{
                ans2[globalmax-currmin] = MAX(maax, ans2[globalmax-currmin]);
                --currmin;
            }
        }

        // Don't forget to consider the max after we run out of edges.
        // As well as to reset all our values one more time.
        ans2[globalmax-currmin] = MAX(maax, ans2[globalmax-currmin]);
        --globalmax;
        maax = 1;
        for (i = 0; i<r*c; ++i){
            size[i] = 1;
            onion[i] = i;
        }
    }

    // Generate the list of answers by walking through the values one by one.
    j = 0;
    for (i=0; i<=r*c; ++i){
        while (i > ans2[j]) ++j;
        ans[i] = j;
    }

    // Printf the answer for each query.
    int n, k;
    scanf("%d", &n);
    while (n--){
        scanf("%d", &k);
        printf("%d\n", ans[k]);
    }

    return 0;
}
