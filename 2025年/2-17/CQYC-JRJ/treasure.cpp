#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, fx[5][3]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, cnt, tot;
vector <int> d[N], vis[N];
struct qwq {
	int x, y;
}zhan[N], clea[N];
vector <qwq> to[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
inline int check(int s, int t, int mx) {
	if(mx > d[s][t]) return 0;
	// debug(s, t, mx, cnt, "?????\n");
	while(cnt)
		vis[clea[cnt].x][clea[cnt].y]=0, --cnt;
	for(int i = 1; i <= mx; ++i)
		// if(to[i].size())
			to[i].clear()/*, to[i].shrink_to_fit()*/;
	// debug("!!!!\n");
	tot = 0;
	zhan[++tot]=qwq {s, t};
	vis[s][t]=1;
	clea[++cnt]=qwq {s, t};
	for(int i = 1; i <= tot && tot < mx; ++i) {
		// debug(i, tot, "???\n");
		for(int j = 0; j < to[i].size(); ++j)
			zhan[++tot]=to[i][j];
		for(int j = 0; j < 4; ++j) {
			int x = zhan[i].x+fx[j][0], y = zhan[i].y+fx[j][1];
			// debug(x, y, n, m, "????\n");
			if(x <= 0 || x > n || y <= 0 || y > m || vis[x][y]) continue;
			// debug(mx-d[x][y], "!!!\n");
			vis[x][y]=1;
			clea[++cnt]=qwq {x, y};
			if(mx-tot <= d[x][y])
				zhan[++tot]=qwq {x, y};
			else
				to[mx-d[x][y]].push_back(qwq {x, y});
		}
	}
	return (tot >= mx);
}

signed main() {
	File("treasure");
	read(n), read(m);
	// d[0].resize(m+2), vis[0].resize(m+2);
	// d[n+1].resize(m+2), vis[n+1].resize(m+2);
	for(int i = 1; i <= n; ++i) {
		d[i].resize(m+2), vis[i].resize(m+2);
		for(int j = 1; j <= m; ++j)
			read(d[i][j]);
	}
	int l = 2, r = 1, ans = 1;
	for(int i = 1; i <= n; ++i)
		r=max(r, max(d[i][m], d[i][1]));
	for(int i = 1; i <= m; ++i)
		r=max(r, max(d[1][i], d[n][i]));
	// debug("???\n");
	if(n == 1) {
		while(l <= r) {
			int mid = ((l+r)>>1), pd = 0;
			// debug(l, r, "-> ");
			for(int i = 1; i <= n && !pd; ++i)
				if(check(i, 1, mid)) {
					pd=1;
					break;
				}
				else if(m != 1 && check(i, m, mid)) {
					pd=1;
					break;
				}
			for(int i = 2; i < m && !pd; ++i)
				if(check(1, i, mid)) {
					pd=1;
					break;
				}
			if(pd)
				ans=mid, l=mid+1;
			else
				r=mid-1;
			// debug(l, r, "?\n");
		}
	}
	else {
		while(l <= r) {
			int mid = ((l+r)>>1), pd = 0;
			// debug(l, r, "-> ");
			for(int i = 1; i <= n && !pd; ++i)
				if(check(i, 1, mid)) {
					pd=1;
					break;
				}
				else if(check(i, m, mid)) {
					pd=1;
					break;
				}
			for(int i = 2; i < m && !pd; ++i)
				if(check(1, i, mid)) {
					pd=1;
					break;
				}
				else if(check(n, i, mid)) {
					pd=1;
					break;
				}
			if(pd)
				ans=mid, l=mid+1;
			else
				r=mid-1;
			// debug(l, r, "?\n");
		}
	}
	write(ans, '\n');
	return 0;
}
