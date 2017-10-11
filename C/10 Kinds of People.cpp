// GIVES A COMPILE ERROR FOR SOME REASON

#include <cstdio>
#include <set>
#include <deque>

int main(){
    int r, c, q, n[1000005], p[1000005]={0}, d=1, e, k, i, j;
    std::deque<int> v;
    std::set<int> s;
    scanf("%d %d", &r, &c);
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            scanf("%d", &n[i*c+j]);
        }
    }
    scanf("%d", &q);
    while (q--){
        int r1, c1, r2, c2;
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        if (p[r1*c+c1] == 0){
            v.push_back(r1*c+c1);
            while (v.size() != 0){
                e = v.front();
                v.pop_front();
                if (s.find(e) == s.end()){
                    s.insert(e);
                    p[e] = d;
                    d++;
                    if (e%c != 0){
                        if (n[e] == n[e-1]){
                            v.push_back(e-1);
                        }
                    }
                    if (e%c != c-1){
                        if (n[e] == n[e+1]){
                            v.push_back(e+1);
                        }
                    }
                    if (e/c != 0){
                        if (n[e] == n[e-r]){
                            v.push_back(e-r);
                        }
                    }
                    if (e/c != r-1){
                        if (n[e] == n[e+r]){
                            v.push_back(e+r);
                        }
                    }
                }
            }
        }
        if (p[r2*c+c2] == 0){
            v.push_back(r2*c+c2);
            while (v.size() != 0){
                e = v.front();
                v.pop_front();
                if (s.find(e) == s.end()){
                    s.insert(e);
                    p[e] = d;
                    d++;
                    if (e%c != 0){
                        if (n[e] == n[e-1]){
                            v.push_back(e-1);
                        }
                    }
                    if (e%c != c-1){
                        if (n[e] == n[e+1]){
                            v.push_back(e+1);
                        }
                    }
                    if (e/c != 0){
                        if (n[e] == n[e-r]){
                            v.push_back(e-r);
                        }
                    }
                    if (e/c != r-1){
                        if (n[e] == n[e+r]){
                            v.push_back(e+r);
                        }
                    }
                }
            }
        }
        if (p[r1*c+c1] == p[r2*c+c2]){
            k = n[r1*c+c1];
            if (k == 0){
                printf("decimal\n");
            }
            else {
                printf("binary\n");
            }
        }
        else {
            printf ("neither\n");
        }
    }
    return 0;
}
