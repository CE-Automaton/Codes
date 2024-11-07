#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
// bool st;
const int N = 55;
int sub, t, n, m, u, v, tt[N], pd, vis[N], col[N];
LL ans, sss, to[N];
vector <int> up[N];
map <LL, LL> ss;

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
void dfs(int x) {
	vis[x]=1;
	for(int y = 0; y < up[x].size(); ++y)
		if(!vis[up[x][y]])
			col[up[x][y]]=(col[x]^1), dfs(up[x][y]);
		else
			pd&=(col[x] != col[up[x][y]]);
}
LL f(LL x) {
	if(ss.count(x)) return ss[x];
	int xx = __lg(x&(-x));
	return ss[x]=(f(x&(x-1))+f(x&to[xx]));
}
// bool fn;
signed main() {
	File("deleted");
	// debug((double) (&st-&fn)*1.0/1024/1024, '\n');
	read(sub);
	read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i)
			up[i].clear(), to[i-1]=0;
		for(int i = 1; i <= m; ++i) {
			read(u), read(v);
			to[u-1]|=(1LL<<(v-1));
			to[v-1]|=(1LL<<(u-1));
			up[u].push_back(v);
			up[v].push_back(u);
		}
		sss=(1LL<<n)-1;
		for(int i = 0; i < n; ++i)
			to[i]=(sss^(to[i]|(1LL<<i)));
		ans=0;
		int gs = 1, ppp = 0, gss = 0;
		for(int i = 1; i <= n; ++i)
			vis[i]=0, col[i]=0;
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
				col[i]=1, pd=1, dfs(i), gs&=pd, ++gss, ppp+=(up[i].size() == 0);
		ss.clear();
		ss[0]=1;
		ans=(f(sss)<<1)+(1LL<<gss)-1LL*gs*(1LL<<gss)-(1LL<<(ppp+1))+1LL*(ppp == gss)*(1LL<<gss);//容斥
		write((1LL<<n)-ans, '\n');
	}
	// debug(clock(), '\n');
	return 0;
}