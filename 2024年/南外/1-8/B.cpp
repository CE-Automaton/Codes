#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, q, uu, vv, kk, dep[N], dfn[N], up[N][21], u[N][21], d[N][21], fr[N], se[N], cnt, too[N<<1], nxt[N<<1], fir[N],
zhan[N], tot, pd[N], p[N], nd[N], cnp[N], ans;
vector <int> to[N], son[N];

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
int comp(int A, int B) {
	return fr[A] > fr[B];
}
void dfs(int x, int fa) {
	dep[x]=dep[fa]+1, dfn[x]=++cnt;
	up[x][0]=fa;
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			son[x].push_back(y);
			if(fr[y]+1 >= fr[x]) se[x]=fr[x], fr[x]=fr[y]+1;
			else if(fr[y]+1 > se[x]) se[x]=fr[y]+1;
		}
	sort(son[x].begin(), son[x].end(), comp);
	for(int y : son[x])
		if(y != fa) {
			if(fr[y]+1 == fr[x]) u[y][0]=se[x]+1, d[y][0]=se[x];
			else u[y][0]=fr[x]+1, d[y][0]=fr[x];
		}
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 18; i >= 0; --i)
		if(up[x][i] && dep[up[x][i]] >= dep[y]) x=up[x][i];
	// debug(x, y, " ");
	for(int i = 18; i >= 0; --i)
		if(up[x][i] && up[y][i] && up[x][i] != up[y][i])
			x=up[x][i], y=up[y][i];
	// debug(x, y, "?\n");
	return (x == y ? x : up[x][0]);
}
int upk(int x, int k) {
	for(int i = 0; i <= 18; ++i)
		if((k>>i)&1)
			x=up[x][i];
	return x;
}
int uk(int x, int k) {
	int ret = 0, now = 0;
	for(int i = 0; i <= 18; ++i)
		if((k>>i)&1)
			ret=max(ret, u[x][i]+now), 
			now|=(1<<i), x=up[x][i];
	return ret;
}
int dk(int x, int k) {
	int ret = 0, now = k;
	for(int i = 0; i <= 18; ++i)
		if((k>>i)&1)
			now^=(1<<i), ret=max(ret, d[x][i]+now), 
			x=up[x][i];
	return ret;
}
int compp(int A, int B) {
	return dfn[A] < dfn[B];
}
void edge(int x, int y) {
	// debug(x,"-> ", y,'\n');
	too[++cnt]=y, nxt[cnt]=fir[x], fir[x]=cnt;
	// too[++cnt]=x, nxt[cnt]=fir[y], fir[y]=cnt;
}
void sol1(int x) {
	nd[x]=(pd[x] ? 0 : inf);
	for(int i = fir[x]; i; i=nxt[i]) {
		sol1(too[i]), nd[x]=min(nd[x], nd[too[i]]+dep[too[i]]-dep[x]);
		int k = upk(too[i], dep[too[i]]-dep[x]-1);
		cnp[k]=1, zhan[++tot]=k;
	}
}
void sol2(int x) {
	ans=max(ans, nd[x]);
	for(int i = fir[x]; i; i=nxt[i]) {
		int d = dep[too[i]]-dep[x];
		nd[too[i]]=min(nd[too[i]], nd[x]+d);
		sol2(too[i]);
		if(d > 1) {
			if(nd[x]-nd[too[i]] == d) //在too[i]子树里
				ans=max(ans, uk(too[i], d-1)+nd[too[i]]);
			else
				if(nd[too[i]]-nd[x] == d)
					ans=max(ans, dk(too[i], d-1)+1+nd[x]);
				else {
					int k = (d-nd[too[i]]+nd[x])/2, upp = upk(too[i], k);
					if(up[upp][0] != x)
						ans=max(ans, dk(upp, dep[upp]-dep[x]-1)+1+nd[x]);
					ans=max(ans, uk(too[i], k)+nd[too[i]]);
				}
		}
	}
	for(int y : son[x])
		if(!cnp[y]) {
			ans=max(ans, fr[y]+1+nd[x]);
			break;
		}
	fir[x]=0;		
}

signed main() {
	File("inception");//写的挺好的题解：https://blog.csdn.net/litble/article/details/86579464
	read(n), read(q);
	for(int i = 2; i <= n; ++i)
		read(uu), read(vv), to[uu].push_back(vv), to[vv].push_back(uu);
	dfs(1, 0);
	for(int i = 1; i <= 18; ++i) {
		for(int j = 1; j <= n; ++j)
			up[j][i]=up[up[j][i-1]][i-1], 
			u[j][i]=max(u[j][i-1], u[up[j][i-1]][i-1]+(1<<(i-1))),
			d[j][i]=max(d[j][i-1]+(1<<(i-1)), d[up[j][i-1]][i-1]);
	}
	while(q--) {
		ans=0;
		read(kk);
		for(int i = 1; i <= kk; ++i)
			read(p[i]), pd[p[i]]=1;
		cnt=0;
		tot=0;
		sort(p+1, p+1+kk, compp);//构造虚树
		zhan[++tot]=1;
		fir[1]=0;
		for(int i = (p[1] == 1 ? 2 : 1); i <= kk; ++i) {
			int lc = lca(zhan[tot], p[i]);
			// debug(p[i], zhan[tot], lc, "!?\n");
			if (lc != zhan[tot]) {
				while(dfn[lc] < dfn[zhan[tot-1]])
					edge(zhan[tot-1], zhan[tot]), --tot;
				if(dfn[lc] > dfn[zhan[tot-1]])
					fir[lc]=0, edge(lc, zhan[tot]), zhan[tot] = lc;
				else
					edge(lc, zhan[tot]), --tot;
			}
			fir[p[i]]=0, zhan[++tot]=p[i];
		}
		while(tot >= 2)
			edge(zhan[tot-1], zhan[tot]), --tot;
		sol1(1);
		sol2(1);
		write(ans, '\n');
		while(tot)
			cnp[zhan[tot]]=0, --tot;
		for(int i = 1; i <= kk; ++i)
			pd[p[i]]=0;
	}
	return 0;
}