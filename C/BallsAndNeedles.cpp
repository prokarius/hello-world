#include <cstdio>
#include <map>
#include <set>

std::map <long long, int> threed, twod;
std::map <int, std::set<int> > adj;

int onion [50005], onion2 [50005];

int findparentonion(int x){
    if (onion[x] == x){
        return x;
    }
    else{
        onion[x] = findparentonion(onion[x]);
        return (onion[x]);
    }
}

int findparentonion2(int x){
    if (onion2[x] == x){
        return x;
    }
    else {
        onion2[x] = findparentonion2(onion2[x]);
        return (onion2[x]);
    }
}

int oniononion (int x, int y){
    int xroot = findparentonion(x);
    int yroot = findparentonion(y);
    if (xroot == yroot){
        return 1;
    }
    onion[xroot] = yroot;
    return 0;
}

int oniononion2 (int x, int y){
    int xroot = findparentonion2(x);
    int yroot = findparentonion2(y);
    if (xroot == yroot){
        return 1;
    }
    onion2[xroot] = yroot;
    return 0;
}

int main(){
    for (int a = 0; a<50005; a++){
    onion [a] = a;
    onion2 [a] = a;
    }
    int n, i = 0, j=0, flor = 0, closed = 0;
    scanf("%d", &n);
    while (n--){
        int vertex1, vertex2, x1, x2, y1, y2, z1, z2;
        long long v1, v2;
        scanf ("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
        v1 = x1 + 1000*y1 + 1000000*z1;
        v2 = x2 + 1000*y2 + 1000000*z2;
        if (not closed){
            if (threed.find(v1) == threed.end()){
                threed[v1] = i;
                vertex1 = i;
                i++;
            }
            else{
                vertex1 = threed[v1];
            }
            if (threed.find(v2) == threed.end()){
                threed[v2] = i;
                vertex2 = i;
                i++;
            }
            else{
                vertex2 = threed[v2];
            }
            closed = oniononion (vertex1, vertex2);
        }
        if (not flor){
            v1 = v1 % 1000000;
            v2 = v2 % 1000000;
            if (v1 != v2){
                if (twod.find(v1) == twod.end()){
                    twod[v1] = j;
                    vertex1 = j;
                    j++;
                }
                else{
                    vertex1 = twod[v1];
                }
                if (twod.find(v2) == twod.end()){
                    twod[v2] = j;
                    vertex2 = j;
                    j++;
                }
                else{
                    vertex2 = twod[v2];
                }
                if (vertex1 > vertex2){
                    int c = vertex2;
                    vertex2 = vertex1;
                    vertex1 = c;
                }
                if (adj.find(vertex1) != adj.end()){
                    if (adj[vertex1].find(vertex2) == adj[vertex1].end()){
                        adj[vertex1].insert(vertex2);
                        flor = oniononion2 (vertex1, vertex2);
                    }
                }
                else {
                    std::set <int> b;
                    b.insert(vertex2);
                    adj[vertex1] = (b);
                    flor = oniononion2(vertex1, vertex2);
                }
            }
        }
    }

    if (closed){
        printf("True closed chains\n");
    }
    else{
        printf("No true closed chains\n");
    }
    if (flor){
        printf("Floor closed chains\n");
    }
    else{
        printf("No floor closed chains\n");
    }
    return 0;
}
