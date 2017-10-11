#include<cstdio>
#include<vector>
#include<algorithm>
#include<stack>
#include<deque>

struct stick {
    double m, c;
    int x1, x2, y1, y2, n;
};

std::stack <struct stick> here;
std::deque<int> ans;
int visited [5005] = {0};
struct stick slist[5005];
std::vector<int> adjlist[5005];

// Returns the y value of the stick at the x value
double gety(struct stick s, int x){
    return s.m * x + s.c;
}

// Tests to see if the sticks affects each other. If not, return 2.
// If b needs to be removed before a, return 1, else return 0
int affect (struct stick a, struct stick b){
    if (b.x1 > a.x2) return 2;
    if (gety(a, b.x1) < b.y1) return 1;
    return 0;
}

// DFS. The highest stick will have no children, it will be at the front
// The solution will then read from the back.
void dfs(int stick){
    int w;
    visited[stick] = 1;
    for (w = 0; w < adjlist[stick].size();++w){
        if (visited[adjlist[stick][w]] != 1) dfs(adjlist[stick][w]);
    }
    ans.push_back(stick+1);
}

int main(){
    double q;
    int i=0, j, N, a,b,c,d;
    scanf ("%d", &N);
    while (i < N){
        scanf ("%d %d %d %d", &a, &b, &c, &d);
        struct stick P;
        // Ensure the sticks are number left edge -> right edge
        if (a > c){
            std::swap (a, c);
            std::swap (b, d);
        }
        P.n = i;
        P.x1 = a;
        P.x2 = c;
        P.y1 = b;
        P.y2 = d;
        if (a == c) q = 0;
        else q = ((double) (d-b))/(c-a);
        P.m = q;
        P.c = b - q*a;
        slist[i] = P;
        ++i;
    }

    // The main shit
    // For each pair see if the sticks affect each other.
    // Ensure the left point of A is to the left of B.
    // Symmetry bitches. <-- This wasted 4 hours of my life.
    // Draw a digraph. A -> B if B is being blocked by A.
    for (i=0; i<N-1; ++i){
        for (j=i+1; j<N; ++j){
            int z;
            if (slist[i].x1 > slist[j].x1){
                z = affect(slist[j], slist[i]);
                if (z==0) adjlist[i].push_back(j);
                else if (z==1) adjlist[j].push_back(i);
            }
            else{
                z = affect(slist[i], slist[j]);
                if (z==0) adjlist[j].push_back(i);
                else if (z==1) adjlist[i].push_back(j);
            }
        }
    }

    // DFS each component
    for (i=0; i<N; ++i){
        if (visited[i] == 0) dfs(i);
    }

    // And reverse the output list, and dump.
    while (ans.size()){
        printf ("%d\n", ans.back());
        ans.pop_back();
    }
    return 0;
}
