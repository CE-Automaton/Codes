#include <bits/stdc++.h>
using namespace std;
const int N = 2e2+5;
int n, mod, inc[N], jc[N], st, dp[N][N][45], vis[N][N][45], ans;

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
int dfs(int x, int y, int z) {
	if(vis[x][y][z]) return dp[x][y][z];
	vis[x][y][z]=1;
	int &ret = dp[x][y][z]; ret=0;
	if(z < st && x < z) return ret;
	if(z == st) {
		if(x < n)
			return ret=inc[n-x];
		return ret;
	}
	int xx = st-z;
	for(int j = 0; x+j <= n && y+j*xx <= n-st+1; ++j) 
        ret=upd(ret+1LL*dfs(x+j, y+j*xx, z+1)*inc[j]%mod);
    return ret;
}

signed main() {
	read(n), read(mod);
	inc[0]=inc[1]=jc[0]=jc[1]=1;
	for(int i = 2; i <= n; ++i)
		inc[i]=1LL*inc[mod%i]*(mod-mod/i)%mod, jc[i]=1LL*i*jc[i-1]%mod;
	for(int i = 1; i <= n; ++i)
		inc[i]=1LL*inc[i-1]*inc[i]%mod;
	for(st = 0; st <= 32; ++st) {
		memset(vis, 0, sizeof vis);
		ans=upd(ans+dfs(0,0,0));
	}
	write(1LL*ans*jc[n]%mod, '\n');
	return 0;
}
