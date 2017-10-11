#include<cstdio>
#include<vector>
#include<stack>
#include<algorithms>

struct line {
    double m, c;
    int x1, x2, y1, y2;
};

int visited[100003] = {0};
struct line llist[100003];
std::vector<int> adjlist[100003];

double gety(struct line L, x){
    return L.m * x + L.c;
}

int main(){
    double q;
    int i=0, N, a, b, c, d;
    scanf("%d", &N);
    while (i < N){
        struct line L;
        scanf ("%d %d %d %d", &a, &b, &c, &d);
        if (a > c){
            std::swap(a,c);
            std::swap(b,d);
        }
        L.x1 = a;
        L.x2 = c;
        L.y1 = b;
        L.y2 = d;
        if (a == c) q = 0;
        else q = ((double) (d-b))/(c-a);
        L.m = q;
        L.c = b-q*a;
        llist[i] = L;
        ++i;
    }

    // DFS



    return 0;
}
