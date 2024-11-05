#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, l[N], r[N], dfn[N], jc[N], inv[N], inc[N], st[N], p[N], ll[N], rr[N], vi[N], gs;
unsigned long long ls, rs;
vector <int> to[N];
unordered_map <LL, int> vis;

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
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int solve(int L, int R, int l, int r) {
	if(l >= r) return 1;
	int tt = vis[L*10000000LL+R];
	return 1LL*solve(L, tt, l, tt-1)*solve(tt, R, tt+1, r)%mod*c(r-l, tt-l)%mod;
}
void dfs(int x) {
	if(x == n+1) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 0; j < i; ++j)
				if(p[i] > p[j])
					ll[i]=j;
			for(int j = n+1; j > i; --j)
				if(p[i] > p[j])
					rr[i]=j;
		}
		unsigned long long ln = 0, rn = 0;
		sort(ll+1, ll+1+n);
		sort(rr+1, rr+1+n);
		for(int i = 1; i <= n; ++i)
			ln=ln*31uLL+ll[i];
		for(int i = 1; i <= n; ++i)
			rn=rn*31uLL+rr[i];
		if(ls == ln && rs == rn)
			++gs;
		return ;
	}
	for(int i = 1; i <= n; ++i)
		if(!vi[i]) {
			vi[i]=1;
			p[x]=i;
			dfs(x+1);
			vi[i]=0;
		}
}

signed main() {
	File("memorable");
	read(n);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		inc[i]=1LL*inc[i-1]*inv[i]%mod, jc[i]=1LL*i*jc[i-1]%mod;
	for(int i = 1; i <= n; ++i)
		read(l[i]);
	for(int i = 1; i <= n; ++i)
		read(r[i]);
	if(n <= 8) {
		// debug("!");
		sort(l+1, l+1+n);
		sort(r+1, r+1+n);
		for(int i = 1; i <= n; ++i)
			ls=ls*31uLL+l[i];
		for(int i = 1; i <= n; ++i)
			rs=rs*31uLL+r[i];
		dfs(1);
		write(gs, '\n');
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		vis[l[i]*10000000LL+r[i]]=i;
	write(solve(0, n+1, 1, n), '\n');
	return 0;
}
/*
5
3 1 0 0 4
6 3 6 3 6
*/