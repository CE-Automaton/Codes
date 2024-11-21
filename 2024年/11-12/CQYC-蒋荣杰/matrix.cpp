#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int T, n, m, p[N], q[N], vis[N], hd[N], viss[N], cnt, ans, d[15][15], tot, zhan[N];
map <LL, int> pdd;
struct qwq {
	int w, x, y;
}b[N];
vector <int> a[N];

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
int comp(qwq A, qwq B) {
	return A.w < B.w;
}
void cf1(int x) {
	for(int j = 1; j <= m; ++j)
		d[x][q[j]]=a[x][j];
	for(int j = 1; j <= m; ++j)
		a[x][j]=d[x][j];
}
void cf2(int x) {
	for(int j = 1; j <= n; ++j)
		d[p[j]][x]=a[j][x];
	for(int j = 1; j <= n; ++j)
		a[j][x]=d[j][x];
}
void dfs() {
	LL lst = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			lst=lst*10LL+a[i][j]+1;
	if(pdd.count(lst)) return ;
	pdd[lst]=1, ++ans;
	int c[12];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			c[i*m-m+j]=a[i][j];
	for(int o = 1; o <= n; ++o) {
		cf1(o);
		dfs();
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				a[i][j]=c[i*m-m+j];
	}
	for(int o = 1; o <= m; ++o) {
		cf2(o);
		dfs();
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				a[i][j]=c[i*m-m+j];
	}
}
int gcdd(int x, int y) {
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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}

signed main() {
	File("matrix");
	read(T);
	while(T--) {
		read(n), read(m);
		ans=0;
		int pd = 1;
		for(int i = 1; i <= n; ++i)
			read(p[i]), pd&=(p[i] == i);
		for(int i = 1; i <= m; ++i)
			read(q[i]);
		for(int i = 1; i <= n; ++i) {
			a[i].clear();
			a[i].resize(m+5);
			for(int j = 1; j <= m; ++j)
				read(a[i][j]);
		}
		if(pd) {
			// debug("sub!\n");
			ans=1;
			for(int i = 1; i <= n; ++i) {
				for(int j = 1; j <= m; ++j) 
					vis[j]=viss[j]=hd[j]=0;
				for(int j = 1; j <= m; ++j) 
					if(!vis[j]) {
						tot = 0;
						int now = j, lll = 0;
						while(!vis[now]) 
							zhan[++tot]=now, vis[now]=1, now=q[now];
						viss[tot]=1;
						for(int k = 1; k <= tot; ++k)
							lll|=(k == 1 ? (a[i][zhan[1]] != a[i][zhan[tot]]) : (a[i][zhan[k]] != a[i][zhan[k-1]]));
						hd[tot]|=lll;
					}
				int ggg = -1, gs = 0;
				for(int j = 1; j <= m; ++j) 
					if(viss[j] && hd[j])
						ans=1LL*ans*j%mod, ++gs;
				if(gs >= 2) {
					for(int j = 1; j <= m; ++j) 
						if(viss[j] && hd[j])
							ggg=(ggg == -1 ? j : gcdd(ggg, j));
					ans=1LL*ans*ksm(ggg, mod-2)%mod;
				}
			}
			write(ans, '\n');
			continue;
		}
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				b[i*m+j-m]=qwq {a[i][j], i, j};
		sort(b+1, b+n*m+1, comp);
		cnt=0;
		for(int i = 1; i <= n*m; ++i) {
			if(i == 1 || b[i].w != b[i-1].w) 
				++cnt;
			// debug(b[i].x, b[i].y, cnt, "??\n");
			a[b[i].x][b[i].y]=cnt;
		}
		pdd.clear();
		dfs();
		write(ans, '\n');
	}
	return 0;
}