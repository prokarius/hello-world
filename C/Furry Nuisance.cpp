#include <cstdio>
#include <vector>
#include <deque>
#include <set>

int visited[10005];
std::vector<int> adjlist[10005];

bool check(int a, int b){
    int i;
    std::set<int> the;
    for (i=0; i<3;++i){
        if (adjlist[a][i] != b) the.insert(adjlist[a][i]);
    }
    for (i=0; i<3;++i) the.insert(adjlist[b][i]);
    return (the.size() > 4);
}

int bfs(int i){
    int j,k,count=0, d3[7]={0};
    std::deque<int> queue;
    queue.push_front(i);
    while (queue.size()){
        int curr = queue.front();
        queue.pop_front();
        if (visited[curr] != 0) continue;
        if (adjlist[curr].size() > 3) return 1;
        else if (adjlist[curr].size() == 3){
            if (count > 5) return 1;
            else d3[count++] = curr;
        }
        visited[curr] = adjlist[curr].size();
        for (j=0; j<adjlist[curr].size(); ++j) queue.push_back(adjlist[curr][j]);
    }
    for (k=0; k<count-1; ++k){
        for (j=k+1; j<count; ++j){
            if (check(d3[j],d3[k])) return 1;
        }
    }
    return 0;
}

int code (int n, int m){
    int i, a, b, c=0, flag=0;
    for (i=0; i<=n; ++i) adjlist[i].clear();
    for (i=0; i<=n; ++i) visited[i]=0;
    while (m--){
        scanf ("%d %d", &a, &b);
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    for (i=1; i<=n; ++i){
        if (visited[i] == 0){
            flag = bfs(i);
            if (flag) break;
        }
    }
    return flag; 
}

int main(){
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF){
        if (code(n,m)) printf ("YES\n");
        else printf ("NO\n");
    }
    return 0;
}
