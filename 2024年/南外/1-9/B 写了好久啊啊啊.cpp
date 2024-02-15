#include <bits/stdc++.h>
#define mod 1000000007
#define xii first
#define yii second
#define File(huawei) freopen(huawei".in","r",stdin),freopen(huawei".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+10;
int n, m, k, u, v, ds[N], jc[N], vis[N], ans1=1, ans2, zhan[15], tot, col[N], 
aa[N], bb[N];
unordered_map <int, int> to[N];
queue <int> q;

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x, int s) {
	if(x == tot+1) {
		int ans3 = jc[s];
		for(int o = 1, i = zhan[1]; o <= tot; ++o, i=zhan[o])
			for(int oo = o+1, j = zhan[o+1]; oo <= tot; ++oo, j=zhan[oo])
				if(to[i].find(j) != to[i].end()) {
					int op = to[i][j];
					ans3=1LL*ans3*(col[i] == col[j] ? aa[op] : bb[op])%mod;
				}
		ans2=upd(ans2+ans3);
		return ;
	}
	for(int i = 1; i <= s; ++i)
		col[zhan[x]]=i, dfs(x+1, s);
	col[zhan[x]]=s+1;
	dfs(x+1, s+1);
}

signed main() {
	File("color");
	read(n), read(m), read(k);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u][v]=i, to[v][u]=i, ++ds[u], ++ds[v], bb[i]=1;
	jc[0]=1;
	for(int i = 1; i <= n; ++i)
		jc[i]=1LL*jc[i-1]*(k-i+1)%mod;
	for(int i = 1; i <= n; ++i)
		if(ds[i] <= 2)
			q.push(i);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		// debug(x, "!");
		if(ds[x] == 0) 
			ans1=1LL*ans1*k%mod;
		else if(ds[x] == 1) {
			int y = (*to[x].begin()).xii, t = (*to[x].begin()).yii;
			ans1=1LL*ans1*upd(1LL*(k-1)*bb[t]%mod+aa[t])%mod;
			--ds[y], ds[x]=0;
			to[y].erase(x);
			to[x].clear();
			if(ds[y] <= 2)
				q.push(y);
			// debug(x, y, aa[t], bb[t]);
		}
		else {
			int y = (*to[x].begin()).xii, t = (*to[x].begin()).yii;
			to[x].erase(to[x].begin());
			int yy = (*to[x].begin()).xii, tt = (*to[x].begin()).yii;
			to[x].erase(to[x].begin());
			ds[x]=0;
			int pd = (to[y].find(yy) != to[y].end() ? to[y][yy] : 0);
			to[y].erase(x), to[yy].erase(x);
			int f = aa[t], ff = aa[tt], g = bb[t], gg = bb[tt];
			aa[t]=upd(1LL*f*ff%mod+1LL*g*gg%mod*(k-1)%mod)%mod;
			bb[t]=upd(1LL*g*gg%mod*(k-2)%mod+upd(1LL*f*gg%mod+1LL*g*ff%mod));
			if(pd) 
				aa[t]=1LL*aa[t]*aa[pd]%mod, 
				bb[t]=1LL*bb[t]*bb[pd]%mod, 
				--ds[y], --ds[yy];
			to[y][yy]=to[yy][y]=t;
			if(pd) {
				if(ds[y] <= 2) q.push(y);
				if(ds[yy] <= 2) q.push(yy);
			}
			// debug(y, yy, aa[t], bb[t]);
		}
	}
	for(int i = 1; i <= n; ++i)
		if(ds[i])
			zhan[++tot]=i;
	// debug(tot, "woc");
	dfs(1, 0);
	// cout<<ans1<<"!?\n";
	write(1LL*ans1*ans2%mod, '\n');
	return 0;
}