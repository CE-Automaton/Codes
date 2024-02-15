#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5;
int n, w, zhan[N], ans;

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
void dfs(int x, int nd, int pw) {
	if(nd < 0) return ;
	if(nd == 0) {
		// for(int i = 1; i <= x-1; ++i)
		// 	debug(zhan[i]), debug(' ');
		// debug("!?\n");
		ans=upd(ans+pw);
		return ;
	}
	zhan[x]=zhan[x-1]+1;
	dfs(x+1, nd-zhan[x], 1LL*pw*w%mod);
	zhan[x]=zhan[x-1]-1;
	if(zhan[x] > 0)
		dfs(x+1, nd-zhan[x], pw);
}

signed main() {
	File("dazzling");
	read(n), read(w);
	for(int i = 1; i <= n; ++i)
		zhan[1]=i, dfs(2, n-i, 1);
	write(ans, '\n');
	return 0;
}