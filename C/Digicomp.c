#include <stdio.h>

int herd[500003], state[500003];
long long marbles[500003];

int main(){
	herd [0] = 0;
	long long n, m;
	scanf ("%lld %lld", &n, &m);
	int i = 0;
	while (i < m){
		int P, Q;
		char L;
		scanf (" %c %d %d", &L, &P, &Q);
		if (herd[P] < herd[i]+1)
			herd[P] = herd[i]+1;
		if (herd[Q] < herd[i]+1)
			herd[Q] = herd[i]+1;
	
	return 0;
}
