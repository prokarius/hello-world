#include <cstdio>
#include <set>
#include <iterator>

int main(){
    long long j=0;
    std::multiset <long long> c;
    char buf[10];
    std::multiset<long long>::iterator it = c.begin();
    while (scanf("%s", buf) != EOF){
        std::multiset<long long>::iterator kb = it;
        if (buf[0] == '#'){
            printf ("%lld\n", (*it)/600002);
            if (c.size() % 2 == 0) --kb;
            else ++kb;
            c.erase(it);
        }
        else {
            long long i=0, ph=0;
            while (buf[i] != '\0'){
                ph *= 10;
                ph += buf[i] - '0';
                ++i;
            }
            ph = ph*600002+j;
            c.insert(ph);
            if (*it > ph && c.size() % 2 == 1) --kb;
            if (*it < ph && c.size() % 2 == 0) ++kb;
            if (c.size() == 1) kb = c.begin();
        }
        it = kb;
        ++j;
    }
    return 0;
}
