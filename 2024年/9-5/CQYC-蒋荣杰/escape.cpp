#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e4+5;
int n, m, f[N], a[N], l, r, vis[N], ans;
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
void dfs(int x) {
	int gs = 0, pdd = vis[x];
	for(int y : to[x])
		dfs(y), gs+=vis[y], vis[x]|=vis[y];
	if(gs >= 2 && !pdd) 
		++ans;
}

signed main() {
	File("escape");
	read(n), read(m);
	int pd = 1;
	for(int i = 2; i <= n; ++i)
		read(f[i]), pd&=(f[i] == i-1), to[f[i]].push_back(i);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	if(pd) {
		for(int i = 1; i <= m; ++i) {
			read(l), read(r);
			write(r-l+1, '\n');
		}
		return 0;
	}
	for(int i = 1; i <= m; ++i) {
		read(l), read(r);
		ans=r-l+1;
		for(int j = 1; j <= n; ++j)
			vis[j]=0;
		for(int j = l; j <= r; ++j)
			vis[a[j]]=1;
		dfs(1);
		write(ans, '\n');
	}
	return 0;
}