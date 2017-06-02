#include <iostream>
#include <deque>

struct line {
    long long m, c;
    void set_value(long long, long long);
    long long yval (long long x);
};

void line::set_value(long long a, long long dp){
    m = -2*a;
    c = a*a + dp;
};

long long line::yval (long long x){
    return m*x + c;
};

std::deque<line> linequeue;

void addline (line l) {
    while (linequeue.size()>1){
        line k = linequeue.back();
        linequeue.pop_back();
        line j = linequeue.back();
        if ((j.c - k.c)*(j.m - l.m) >= (l.c - j.c)*(k.m - j.m)){
            linequeue.push_back(k);
            break;
        }
    }
    linequeue.push_back(l);
}

void check (long long x){
    while (linequeue.size()>1){
        line e = linequeue.front();
        linequeue.pop_front();
        line r = linequeue.front();
        if (e.yval(x) < r.yval(x)){
            linequeue.push_front (e);
            break;
        }
    }
}

long long yvalue (long long a){
    line v = linequeue.front();
    return v.yval(a);
}

int main (){
    std::ios::sync_with_stdio(false);
    long long n, c, a, i, output = 0;
    std::cin >> n >> c;
    for (i = 0; i < n; i++){
        std::cin >> a;
        line newline;
        newline.set_value(a, output);
        addline(newline);
        check (a);
        output = yvalue(a)+ a*a + c;
    }
    std::cout << output;
    return 0;
}
