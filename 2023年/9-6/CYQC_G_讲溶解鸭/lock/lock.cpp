#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 2e5+5;
int n, l, a[N], b[N], ans;

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
void dfs(int x, int sa, int sb) {
	if(sa <= l)
		ans=max(ans, sb);
	if(x == n+1) return ;
	dfs(x+1, sa, sb);
	dfs(x+1, (sa^a[x]), (sb^b[x]));
}

signed main() {
	freopen("lock.in", "r", stdin);
	freopen("lock.out", "w", stdout);
	read(n), read(l);
	for(int i = 1; i <= n; ++i)
		read(a[i]), read(b[i]);
	dfs(1, 0, 0);
	write(ans, '\n');
	return 0;
}
