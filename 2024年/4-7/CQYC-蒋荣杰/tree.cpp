#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 1e5+5;
int T, n, dep[N], a[N], b[N], u, v, rt, ds[N], zhan[N], tot, op[N], tt;
vector <int> to[N];
char s[N], t[N];

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
void dfs(int x, int fa) {
	if(!tot || zhan[tot] != a[x])
		zhan[++tot]=a[x];
	if(!tt || op[tt] != b[x])
		op[++tt]=b[x];
	for(int i = 0; i < to[x].size(); ++i) {
		int y = to[x][i];
		if(y != fa)
			dfs(y, x);
	}
}
void dfss(int x, int fa) {
	dep[x]=dep[fa]+1;
	for(int i = 0; i < to[x].size(); ++i) {
		int y = to[x][i];
		if(y != fa)
			dfss(y, x);
	}
}

signed main() {
	File("tree");
	read(T);
	while(T--) {
		read(n);
		scanf("%s\n%s", s+1, t+1);
		int pd = 1;
		for(int i = 1; i <= n; ++i)
			a[i]=s[i]-'0', b[i]=t[i]-'0', to[i].clear(), 
			pd&=(a[i] == b[i]), ds[i]=0;
		for(int i = 2; i <= n; ++i)
			read(u), read(v), to[u].push_back(v), to[v].push_back(u), ++ds[u], ++ds[v];
		if(pd) {
			puts("TAK");
			continue;
		}
		pd=1;
		for(int i = 2; i <= n; ++i)
			pd&=(a[i] == a[i-1]);
		if(pd) {
			puts("NIE");
			continue;
		}
		u=0;
		for(int i = 1; i <= n; ++i)
			if(ds[i] > ds[u])
				u=i;
		if(ds[u] <= 2) {
			for(int i = 1; i <= n; ++i)
				if(ds[i] == 1)
					v=i;
			tot=0, tt=0;
			dfs(v, 0);
			if(tot < tt || zhan[1] != op[1]) 
				puts("NIE");
			else
				puts("TAK");
			continue;
		}
		dfss(u, 0);
		pd=1;
		for(int i = 1; i <= n; ++i)
			pd&=(b[i] == (b[u]^(dep[i]%2 == 1 ? 0 : 1)));
		if(pd)
			puts("NIE");
		else
			puts("TAK");
	}
	return 0;
}