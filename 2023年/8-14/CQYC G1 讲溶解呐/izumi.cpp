#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const int N = 2e5+5;
int n, m, l, r, a[N], b[N];
__int128 ans;
unordered_map <uLL, pair<int, __int128> > qwq;

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
	freopen("izumi.in", "r", stdin);
	freopen("izumi.out", "w", stdout);
	read(n), read(m);
	srand(time(0));
	for(int i = 1; i <= n; ++i) {
		read(l), read(r);
		uLL now = 1ull*RAND_MAX*RAND_MAX*RAND_MAX*RAND_MAX*rand()+1ull*RAND_MAX*RAND_MAX*RAND_MAX*rand()+1ull*RAND_MAX*RAND_MAX*rand()+1ull*RAND_MAX*rand()+1ull*rand();
		a[l+1]^=now, a[r+1]^=now;
		++b[l], --b[r+1];
	}
	for(int i = 1; i <= m; ++i)
		b[i]+=b[i-1], a[i]^=a[i-1];
	for(int i = 1; i <= m; ++i)
		a[i]^=a[i-1];
	for(int i = 1; i <= m; ++i) {
		pair<int, __int128>& gs = qwq[a[i]];
		++gs.first;
		gs.second+=i-1;
		ans+=(__int128) i*gs.first-gs.second;
	}
	int lst = 0;
	for(int i = 1; i <= m; ++i)
		if(b[i] == 0)
			++lst, ans-=(__int128) lst*(lst+1)/2;
		else
			lst=0;
	write(ans, '\n');
	return 0;
}
