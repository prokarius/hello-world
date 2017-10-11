#include<map>
#include<cstdio>
#include<string>

int cards[1004], state[1004];

int main(){
    char x[23], y[23];
    int q, i, n, ph, a, b, c, d, output = 0;
    std::map <std::string, int> themap;
    scanf("%d %d", &n, &ph);
    q = n;
    for (i=0; i<1004; ++i){
        cards[i] = -1;
        state[i] = 0;
    }
    while (ph--){
        scanf("%d %d %s %s", &a, &b, x, y);
        std::string xs(x);
        std::string ys(y);
        if (themap.find(xs) == themap.end()){
            c = themap.size();
            themap[xs] = c;
        }
        else c = themap[xs];
        if (themap.find(ys) == themap.end()){
            d = themap.size();
            themap[ys] = d;
        }
        else d = themap[ys];

        if (c == d){
            state[a] = -1;
            state[b] = -1;
        }
        else{
            if ((state[a] >> 1) % 2 == 0) state[a] += 2;
            if ((state[b] >> 1) % 2 == 0) state[b] += 2;

            if (cards [2*c] == -1) cards[2*c] = a;
            else if (cards[2*c] != a){
                cards[1+2*c] = a;
                if (state[a] %2 == 0) ++state[a];
                if (state[cards[2*c]] %2 == 0) ++state[cards[2*c]];
            }
            if (cards [2*d] == -1) cards[2*d] = b;
            else if (cards[2*d] != b){
                cards[1+2*d] = b;
                if (state[b] %2 == 0) ++state[b];
                if (state[cards[2*d]] %2 == 0) ++state[cards[2*d]];
            }
        }
    }
    a=b=c=d=0;
    for (i=1; i<=n; ++i){
        if (state[i] == 0) ++d;
        else if (state[i] == 2) ++c;
        else if (state[i] == 3) ++b;
        else ++a;
    }
    output += b/2;
    if (c == d) output += c;
    else if (d == 2) ++output;
    printf ("%d\n", output);
    return 0;
}
