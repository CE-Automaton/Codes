#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
// bool st;
const int N = 55, M = (1<<21)+3;
int sub, t, n, m, u, v, tt[N], pd, vis[N], col[N], dp[M][2], sum[M];
LL ans, ddp[N][2];
vector <int> to[N][3], up[N];

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
void ddfs(int x, int fa) {
	ddp[x][0]=1;
	ddp[x][1]=1;
	for(int y = 0; y < up[x].size(); ++y)
		if(up[x][y] != fa) {
			ddfs(up[x][y], x);
			ddp[x][0]=ddp[x][0]*(ddp[up[x][y]][0]+ddp[up[x][y]][1]);
			ddp[x][1]=ddp[x][1]*ddp[up[x][y]][0];
		}
}
// bool fn;
signed main() {
	File("deleted");
	// debug((double) (&st-&fn)*1.0/1024/1024, '\n');
	read(sub);
	if(sub == 17 || sub == 18) {
		read(t);
		while(t--) {
			read(n), read(m);
			for(int i = 1; i <= n; ++i)
				up[i].clear();
			for(int i = 1; i <= m; ++i)
				read(u), read(v), up[u].push_back(v), up[v].push_back(u);
			ddfs(1, 0);
			ans=((ddp[1][0]+ddp[1][1])<<1)-2LL;
			write((1LL<<n)-ans, '\n');
		}
		return 0;
	}
	read(t);
	while(t--) {
		read(n), read(m);//T*(n/2)*2^(n/2)，只能过n小于等于40的点
		int md = (n+1)/2, sss = 0;
		for(int i = 1; i <= n; ++i)
			up[i].clear(), to[i][0].clear(), to[i][1].clear(), to[i][2].clear();
		for(int i = 1; i <= m; ++i) {
			read(u), read(v);
			up[u].push_back(v), up[v].push_back(u);
			if(u <= md && v <= md)
				to[u][0].push_back(v),
				to[v][0].push_back(u)/*, 
				debug(0, u, v, "???\n")*/;
			else 
				if(u > md && v > md)
					to[u-md][1].push_back(v-md), 
					to[v-md][1].push_back(u-md)/*, 
					debug(1, u-md, v-md, "???\n")*/;
				else {
					if(u > v) swap(u, v);
					v-=md;
					to[u][2].push_back(v);
					// debug(2, u, v, "???\n");
				}
		}
		sss=(1<<md);
		for(int i = 0; i < sss; ++i)
			dp[i][0]=0;
		dp[0][0]=1;
		for(int i = 1; i <= md; ++i) {
			tt[i]=0;
			for(int j = 0; j < to[i][2].size(); ++j)
				tt[i]|=(1<<(to[i][2][j]-1));
			int ttt = 0;
			for(int j = 0; j < to[i][0].size(); ++j)
				if(to[i][0][j] < i)
					ttt|=(1<<(to[i][0][j]-1));
			for(int j = 0; j < (1<<(i-1)); ++j)
				if(!(j&ttt))
					dp[(1<<(i-1))|j][0]|=dp[j][0];
		}
		sss=(1<<(n-md));
		for(int i = 0; i < sss; ++i)
			dp[i][1]=0, sum[i]=0;
		dp[0][1]=1;
		for(int i = 1; i <= n-md; ++i) {
			int ttt = 0;
			for(int j = 0; j < to[i][1].size(); ++j)
				if(to[i][1][j] < i)
					ttt|=(1<<(to[i][1][j]-1));
			for(int j = 0; j < (1<<(i-1)); ++j)
				if(!(j&ttt))
					dp[(1<<(i-1))|j][1]|=dp[j][1];
		}
		for(int i = 0; i < sss; ++i)
			sum[i]=dp[i][1];
		for(int o = 0; o < n-md; ++o)
			for(int i = 0; i < sss; ++i)
				if((i>>o)&1)
					sum[i]+=sum[i^(1<<o)];
		ans=0;
		for(int i = 0; i < (1<<md); ++i) {
			int ttt = 0;
			for(int j = 0; j < md; ++j)
				if((i>>j)&1)
					ttt|=tt[j+1];
			ans+=1LL*dp[i][0]*sum[(sss-1)^ttt];
		}
		// debug(ans, '\n');
		int gs = 1, ppp = 0, gss = 0;
		for(int i = 1; i <= n; ++i)
			vis[i]=0, col[i]=0;
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
				col[i]=1, pd=1, dfs(i), gs&=pd, ++gss, ppp+=(up[i].size() == 0);
		ans=(ans<<1)+(1LL<<gss)-1LL*gs*(1LL<<gss)-(1LL<<(ppp+1))+1LL*(ppp == gss)*(1LL<<gss);//容斥
		write((1LL<<n)-ans, '\n');
	}
	// debug(clock(), '\n');
	return 0;
}