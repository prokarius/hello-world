#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
    long long distance;
    int judge;
    int house;
} Edge;

typedef struct{
    int x;
    int y;
} Point;

Point point(int x, int y){
    Point new;
    new.x = x;
    new.y = y;
    return new;
}

long long distance(Point a, Point b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return (dx*dx + dy*dy);
}

// Given judge a, and judge b. Create an edge
Edge getDistance(long long distance, int judge, int house){
    Edge out;
    out.distance = distance;
    out.judge = judge;
    out.house = house;
    return out;
}

int cmpfunc(const void* a, const void* b){
    Edge first = *(Edge*) a;
    Edge second = *(Edge*) b;
    if (first.distance != second.distance){
        return (first.distance > second.distance) - (second.distance > first.distance);
    }
    if (first.judge != second.judge){
        return first.judge > second.judge;
    }
    return first.house > second.house;
}

Edge edgelist[1<<20];

Point judges[1<<10];
Point tar[1<<10];
Point feather[1<<10];

// These just let me know which judges have been selected before
int judgeTar[1<<10];
int tarJudge[1<<10];
int judgeFeather[1<<10];
int featherJudge[1<<10];

int main(){
    // Scan in input
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    for (int i = 0; i < n; ++i){
        int x, y;    
        scanf("%d %d", &x, &y);
        judges[i] = point(x, y);
    }

    for (int i = 0; i < m; ++i){
        int x, y;    
        scanf("%d %d", &x, &y);
        tar[i] = point(x, y);
    }

    // Get the distances
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            long long dist = distance(judges[i], tar[j]);
            edgelist[i*m + j] = getDistance(dist, i, j);
        }
    }

    qsort(edgelist, n*m, sizeof(Edge), cmpfunc);

    // Simply simulate:
    double out = 0;
    int curr = 0;
    int judgesLeft = n;

    while(judgesLeft){
        // Have we assigned the judge / house already?
        if (judgeTar[edgelist[curr].judge] || tarJudge[edgelist[curr].house]){
            curr++;
            continue;
        }

        // Cool we have not.
        out += sqrt(edgelist[curr].distance);
        judgeTar[edgelist[curr].judge] = 1;
        tarJudge[edgelist[curr].house] = 1;
        curr++;
        judgesLeft--;
    }

    // Repeat the steps for the feather houses
    for (int i = 0; i < p; ++i){
        int x, y;    
        scanf("%d %d", &x, &y);
        feather[i] = point(x, y);
    }

    // Get the distances
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < p; ++j){
            long long dist = distance(judges[i], feather[j]);
            edgelist[i*p + j] = getDistance(dist, i, j);
        }
    }

    qsort(edgelist, n*p, sizeof(Edge), cmpfunc);

    // Simply simulate:
    curr = 0;
    judgesLeft = n;

    while(judgesLeft){
        // Have we assigned the judge / house already?
        if (judgeFeather[edgelist[curr].judge] || featherJudge[edgelist[curr].house]){
            curr++;
            continue;
        }

        // Cool we have not.
        out += sqrt(edgelist[curr].distance);
        judgeFeather[edgelist[curr].judge] = 1;
        featherJudge[edgelist[curr].house] = 1;
        curr++;
        judgesLeft--;
    }

    // Print the output
    printf("%lf\n", out);

    return 0;
}

