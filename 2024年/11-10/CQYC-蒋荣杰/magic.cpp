#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, u, v, ds[N], zhan[N], tot, cnt, l[N], r[N], ll[N], rr[N];
LL w[N], ww[N], www[N], sm[N], ans[N], aaa[N], f[N][2];
vector <int> to[N];

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
void ddfs(int x, int fa) {
	aaa[++cnt]=w[x];
	for(int y : to[x])
		if(y != fa)
			ddfs(y, x);
}
void sub(int x) {
	// debug("sub!\n");
	ddfs(x, 0);
	tot=0;
	for(int i = 1; i <= n; ++i) {
		rr[i]=n+1;
		while(tot && aaa[zhan[tot]] <= aaa[i])
			rr[zhan[tot]]=i, --tot;
		zhan[++tot]=i;
	}
	tot=0;
	for(int i = 1; i <= n; ++i) {
		while(tot && aaa[zhan[tot]] < aaa[i])
			--tot;
		ll[i]=zhan[tot];
		zhan[++tot]=i;
	}
	tot=0;
	for(int i = n; i >= 1; --i) {
		while(tot && aaa[i] <= aaa[zhan[tot]])
			l[zhan[tot]]=i, --tot;
		zhan[++tot]=i;
	}
	tot=0;
	for(int i = n; i >= 1; --i) {
		while(tot && aaa[i] < aaa[zhan[tot]])
			--tot;
		r[i]=(tot ? zhan[tot] : n+1);
		zhan[++tot]=i;
	}
	for(int i = 1; i <= n; ++i) 
		ans[i]=-inf;
	ans[0]=0;
	for(int i = 1; i <= n; ++i) {
		ans[i]=max(ans[i], ans[i-1]);
		if(l[i] != 0)
			ans[i]=max(ans[i], ans[l[i]-1]+aaa[l[i]]);
		if(r[i] != n+1)
			ans[r[i]]=max(ans[r[i]], ans[i-1]+aaa[r[i]]);
		if(ll[i] != 0)
			ans[i]=max(ans[i], ans[ll[i]-1]+aaa[i]);
		if(rr[i] != n+1)
			ans[rr[i]]=max(ans[rr[i]], ans[i-1]+aaa[i]);
		// debug(l[i], r[i], ll[i], rr[i], "???\n");
	}
	write(ans[n], '\n');
}
void dddfs(int x, int fa) {
	LL sum = 0;
	for(int y : to[x])
		if(y != fa)
			dddfs(y, x), sum+=max(f[y][0], f[y][1]);
	f[x][0]=sum;
	f[x][1]=0;
	for(int y : to[x])
		if(y != fa)
			f[x][1]=max(f[x][1], sum-max(f[y][0], f[y][1])+min(w[x], w[y])+f[y][0]);
}
// void subb() {
// 	debug("sub2!\n");
// 	dddfs(1, 0);
// 	write(max(f[1][0], f[1][1]), '\n');
// }
void dfs(int x, int fa, LL wwww) {
	if(w[x] >= ww[x])
		zhan[++tot]=x;
	www[x]=wwww;
	for(int y : to[x])
		if(y != fa)
			sm[x]+=ans[y];
	for(int y : to[x])
		if(y != fa)
			sm[y]=sm[x]-ans[y], ww[y]=max(ww[x], w[x]), dfs(y, x, wwww);
}
void sol(int x, int fa) {
	LL sum = 0;
	for(int y : to[x])
		if(y != fa)
			sol(y, x), sum+=ans[y];
	tot=0;
	ww[x]=-inf;
	ans[x]=sum;
	for(int y : to[x])
		if(y != fa) {
			sm[y]=0, www[y]=ans[y], ww[y]=-inf;
			int lst = tot;
			dfs(y, x, ans[y]);
			for(int i = lst+1; i <= tot; ++i) {
				if(w[zhan[i]] <= w[x])
					ans[x]=max(ans[x], sum-www[zhan[i]]+w[zhan[i]]+sm[zhan[i]]);
				if(w[x] <= w[zhan[i]]) {
					if(w[x] >= ww[zhan[i]])
						ans[x]=max(ans[x], sum-www[zhan[i]]+w[x]+sm[zhan[i]]);
					for(int j = 1; j <= lst; ++j)
						if(min(w[zhan[i]], w[zhan[j]]) >= max(ww[zhan[i]], max(ww[zhan[j]], w[x])))
							ans[x]=max(ans[x], sum+min(w[zhan[i]], w[zhan[j]])-www[zhan[i]]-www[zhan[j]]+sm[zhan[i]]+sm[zhan[j]]);
				}
			}
		}
}

signed main() {
	File("magic");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(w[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), ++ds[u], ++ds[v], 
		to[u].push_back(v), to[v].push_back(u);
	int pd = 1, rt = 1;
	for(int i = 1; i <= n; ++i) {
		if(ds[i] == 1)
			rt = i;
		pd&=(ds[i] <= 2);
	}
	if(pd) {
		sub(rt);
		return 0;
	}
	else {
		// pd=1;
		// for(int i = 1; i <= n; ++i)
		// 	pd&=(w[i] <= 2);
		// if(pd) {
		// 	subb();
		// 	return 0;
		// }
		// else {
			sol(1, 0);
			write(ans[1], '\n');
			// debug(clock(), '\n');
		// }
	}
	return 0;
}
