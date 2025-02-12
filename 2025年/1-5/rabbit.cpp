#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 55, mod1 = 998244353, mod2 = 1000000007, base = 10007;
int n, p, gs[N][2/*+、-*/], tot, c[N][N], hs1, hs2, ppp;
map <LL, int> vis[N];
struct qwq {
	int gss[N][2];
}zhan[10005];
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
int upd(int x) {
	return (x >= p ? x-p : x);
}
int upd1(int x) {
	return (x >= mod1 ? x-mod1 : x);
}
int upd2(int x) {
	return (x >= mod2 ? x-mod2 : x);
}
void add(int x, int xx, int yy) {
	for(int i = 1; i <= n; ++i)
		gs[i][0]=gs[i][1]=0;
	for(int i = 1; i <= n; ++i)
		gs[i+1][0]=zhan[xx].gss[i][0], gs[i+1][1]=zhan[xx].gss[i][1];
	for(int i = 1; i <= n; ++i)
		gs[i][0]+=zhan[yy].gss[i][1], gs[i][1]+=zhan[yy].gss[i][0];
	hs1 = 0, hs2 = 0;
	for(int i = 1; i <= x; ++i)
		hs1=upd1(1LL*hs1*base%mod1+gs[i][0]+1), 
		hs1=upd1(1LL*hs1*base%mod1+gs[i][1]+1), 
		hs2=upd2(1LL*hs2*base%mod2+gs[i][0]+1), 
		hs2=upd2(1LL*hs2*base%mod2+gs[i][1]+1);
	if(vis[x].find(1000000000LL*hs2+hs1) == vis[x].end()) {
		vis[x][1000000000LL*hs2+hs1]=1;
		++tot;
		for(int i = 1; i <= n; ++i)
			zhan[tot].gss[i][0]=gs[i][0], zhan[tot].gss[i][1]=gs[i][1];
		to[x].push_back(tot);
	}
	swap(xx, yy);
	for(int i = 1; i <= n; ++i)
		gs[i][0]=gs[i][1]=0;
	for(int i = 1; i <= n; ++i)
		gs[i+1][0]=zhan[xx].gss[i][0], gs[i+1][1]=zhan[xx].gss[i][1];
	for(int i = 1; i <= n; ++i)
		gs[i][0]+=zhan[yy].gss[i][1], gs[i][1]+=zhan[yy].gss[i][0];
	hs1 = 0, hs2 = 0;
	for(int i = 1; i <= x; ++i)
		hs1=upd1(1LL*hs1*base%mod1+gs[i][0]+1), 
		hs1=upd1(1LL*hs1*base%mod1+gs[i][1]+1), 
		hs2=upd2(1LL*hs2*base%mod2+gs[i][0]+1), 
		hs2=upd2(1LL*hs2*base%mod2+gs[i][1]+1);
	if(vis[x].find(1000000000LL*hs2+hs1) == vis[x].end()) {
		vis[x][1000000000LL*hs2+hs1]=1;
		++tot;
		for(int i = 1; i <= n; ++i)
			zhan[tot].gss[i][0]=gs[i][0], zhan[tot].gss[i][1]=gs[i][1];
		to[x].push_back(tot);
	}
}

signed main() {
	read(n), read(p);
	for(int i = 0; i <= n; ++i)
		c[i][0]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			c[i][j]=upd(c[i-1][j-1]+c[i-1][j]);
	gs[1][0]=1;
	++tot;
	zhan[tot].gss[1][0]=1;
	to[1].push_back(1);
	for(int i = 2; i <= n; ++i)
		for(int j = 1; j+j <= i; ++j) {
			int k = i-j;
			for(int o : to[j])
				for(int p : to[k])
					add(i, o, p);
		}
	for(int i : to[n]) {
		for(int k = 1; k <= n; ++k)
			gs[k][0]=zhan[i].gss[k][0], gs[k][1]=zhan[i].gss[k][1];
		int sum = n, ans = 1;
		for(int k = 1; k <= n; ++k)
			ans=1LL*ans*c[sum][gs[k][0]]%p, sum-=gs[k][0], 
			ans=1LL*ans*c[sum][gs[k][1]]%p, sum-=gs[k][1];
		ppp=upd(ppp+ans);
	}
	write(ppp, '\n');
	return 0;
}