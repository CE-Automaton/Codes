#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, q, m, c, vis[N], zhan[N], tot, dis[N], huan[N], cnt, up[N], tt[N];
vector <int> to[N];

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
void ycl(int x) {
	for(int y : to[x]) 
		if(dis[y] == 0)
			dis[y]=dis[x]+1, up[y]=up[x], ycl(y);
}
void dfs(int x, int fa) {
	zhan[++tot]=x;
	vis[x]=tot;
	for(int y : to[x]) {
		if(y == fa) continue;
		if(vis[y]) {
			for(int i = vis[y]; i <= tot; ++i)
				dis[zhan[i]]=1, huan[++cnt]=zhan[i], up[zhan[i]]=zhan[i], tt[zhan[i]]=cnt;
		}
		else
			dfs(y, x);
	}
	--tot;
}

signed main() {
	freopen("catch.in", "r", stdin);
	freopen("catch.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(m), read(c), to[m].push_back(c), to[c].push_back(m);
	dfs(1, 0);
//	for(int i = 1; i <= n; ++i)
//		write(i, ':'), write(up[i], ','), write(dis[i], '\n');
//	for(int i = 1; i <= cnt; ++i)
//		cout<<huan[i]<<" ";
	for(int i = 1; i <= cnt; ++i)
		ycl(huan[i]);
	for(int i = 1; i <= q; ++i) {
		read(m), read(c);
		if(dis[m] == 1) 
			putchar('N'), putchar('o'), putchar('\n');
		else {
			int ms = dis[m]-1, 
				cs = dis[c]-1+min((tt[up[c]]-tt[up[m]] < 0 ? tt[up[c]]-tt[up[m]]+cnt : tt[up[c]]-tt[up[m]]),
				(tt[up[m]]-tt[up[c]] < 0 ? tt[up[m]]-tt[up[c]]+cnt : tt[up[m]]-tt[up[c]]));
//			write(ms, ' '), write(cs, '\n');
			if(ms < cs) 
				putchar('N'), putchar('o'), putchar('\n');
			else
				putchar('Y'), putchar('e'), putchar('s'), putchar('\n');
		}
	}
	return 0;
}
