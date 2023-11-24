#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int N = 1e4+5;
int n, g, l, q, x, ans[N], zhan[N];

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
int gcd(int x, int y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}
void dfs(int x, int lst, int gg, int lcc) {
//	for(int i = 1; i <= x-1; ++i)
//		cout<<zhan[i]<<" ";
//	cout<<"<"<<gg<<", "<<lcc<<">!\n";
	if(gg < g || lcc > l) return ;
	if(gg == g && lcc == l)
		for(int i = 1; i <= x-1; ++i)
			++ans[zhan[i]];
	if(x == n+1) 
		return ;
	for(int i = lst+1; i <= n; ++i)
		zhan[x]=i, dfs(x+1, i, (gg == 1565416546 ? i : gcd(gg, i)), (lcc == -1 ? i : lcc*i/gcd(lcc, i)));
}

signed main() {
	freopen("lcm.in", "r", stdin);
	freopen("lcm.out", "w", stdout);
	read(n), read(g), read(l);
	dfs(1, 0, 1565416546, -1);
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(x);
		write(ans[x], '\n');
	}
	return 0;
}
