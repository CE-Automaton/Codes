#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, m, kk, u, v, A[305][307][307], ans;

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
	return (x >= mod ? x-mod : x);
}
int dfs(int now, int x) {
	if(x == 1) 
		return A[now][1][1];
	if(x == 2)
		return upd(1LL*A[now][1][1]*A[now][2][2]%mod-1LL*A[now][1][2]*A[now][2][1]%mod+mod);
	if(x == 3)
		return upd(upd(upd(1LL*A[now][1][1]*A[now][2][2]%mod*A[now][3][3]%mod-1LL*A[now][3][1]*A[now][2][2]%mod*A[now][1][3]%mod+mod)+upd(1LL*A[now][1][2]*A[now][2][3]%mod*A[now][3][1]%mod-1LL*A[now][3][2]*A[now][2][3]%mod*A[now][1][1]%mod+mod))+upd(1LL*A[now][1][3]*A[now][2][1]%mod*A[now][3][2]%mod-1LL*A[now][3][3]*A[now][2][1]%mod*A[now][1][2]%mod+mod));
	int ret = 0;
	for(int i = 1, noww = 1; i <= x; ++i, noww=-noww) {
		if(A[now][1][i] == 0) continue;
		for(int j = 2; j <= x; ++j)
			for(int k = 1; k <= x; ++k)
				if(k != i)
					A[now+1][j-1][k-(k >= i)]=A[now][j][k];
		ret=upd(ret+1LL*upd(noww+mod)*dfs(now+1, x-1)%mod*A[now][1][i]%mod);
	}
	return ret;
}

signed main() {
	File("deuterium");
	read(n), read(m), read(kk);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), A[1][u][v]=A[1][v][u]=1;
	ans=dfs(1, n);
	write(ans, '\n');
	return 0;
}