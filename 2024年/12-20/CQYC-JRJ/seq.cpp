#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 205;
int n, zhan[N], vis[N], viss[N], gs[N];

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
void dfs(int x) {
	if(x == n+1) {
		for(int i = 1; i <= n; ++i) {
			vis[zhan[i]]=1;
			if(zhan[i] == 1 || vis[zhan[i]-1])
				viss[zhan[i]]=1;
		}
		int pd = 1;
		for(int i = 1; i <= n; ++i)
			pd&=(viss[zhan[i]]);
		if(pd)
			for(int i = 1; i <= n; ++i)
				++gs[zhan[i]];
		for(int i = 1; i <= n; ++i)
			vis[zhan[i]]=viss[zhan[i]]=0;
		return ;
	}
	for(int i = 1; i <= n; ++i)
		zhan[x]=i, dfs(x+1);
}

signed main() {
	File("seq");
	read(n);
	dfs(1);
	for(int i = 1; i <= n; ++i)
		write(gs[i], ' ');
	return 0;
}