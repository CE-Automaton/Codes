#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long uLL;
const int N = 2e5+5;
int op[N];
struct qwq {
	int t;
	uLL w;
	bool operator <(const qwq& A) const {
		return A.w < w;
	}
}; 
priority_queue <qwq> q;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}

signed main() {
	srand(time(0));
	int n = 1000, tt = 1;
	write(n, '\n');
	for(int i = 2; i <= tt; ++i) 
		write(i-1, ' ');
	for(int i = tt+1; i <= n; ++i) {
		if(q.empty() || rand()%100 == 0)
			write(tt, ' ');
		else
			write(q.top().t, ' '), q.pop();
		q.push(qwq {i, 1uLL*RAND_MAX*RAND_MAX*rand()+1uLL*RAND_MAX*rand()+1uLL*rand()});
	}
	putchar('\n');
	for(int i = 1; i <= n; ++i)
		write(rand()%2, ' ');
	return 0;
}
