#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 65, M = 11311531;
int n, a[N][N], w[N][N], now, ans[M], tot;
unordered_map <int, int> vis;

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
void dfs(int x, int ww) {
	if(vis.find(ww) == vis.end())
		vis[ww]=1;
	for(int i = 1; i <= n; ++i)
		if(!((x>>(i-1))&1)) {
			for(int j = i+1; j <= n; ++j)
				if(!((x>>(j-1))&1)) 
					dfs(x|(1<<(i-1))|(1<<(j-1)), ww^w[i][j]);
		}
}

signed main() {
	File("xor");
	read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			read(a[i][j]);
	for(int i = 1; i <= n; ++i) {
		now^=a[i][i];
		for(int j = i+1; j <= n; ++j)
			w[i][j]=w[j][i]=(a[i][i]^a[j][j]^a[i][j]^a[j][i]);
	}
	dfs(0, now);
	now=0;
	for(int i = 1; i <= n; ++i) {
		now^=a[n-i+1][i];
		for(int j = i+1; j <= n; ++j)
			w[i][j]=w[j][i]=(a[n-i+1][i]^a[n-j+1][j]^a[n-i+1][j]^a[n-j+1][i]);
	}
	dfs(0, now);
	for(auto x : vis)
		ans[++tot]=x.first;
	sort(ans+1, ans+1+tot);
	for(int i = 1; i <= tot; ++i)
		write(ans[i], ' ');
	return 0;
}