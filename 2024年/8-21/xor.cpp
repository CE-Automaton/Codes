#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, x, a, gs, pw[N];
struct qwq {
	int to[2], cnt;
}tr[N*30];

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
int dfs(int u, int v, int d) {
	if(!u) return pw[tr[v].cnt];
	if(!v) return pw[tr[u].cnt];
	if(u == v) {
		if(d < 0) return pw[tr[u].cnt];
		if((x>>d)&1) 
			return dfs(tr[u].to[0], tr[u].to[1], d-1);//放一起考虑求个数
		else
			return upd(upd(dfs(tr[u].to[0], tr[u].to[0], d-1)+dfs(tr[u].to[1], tr[u].to[1], d-1))-1+mod);//不能同时有左右儿子，且减去空集
	}
	else {
		if(d < 0) return pw[tr[u].cnt+tr[v].cnt];
		if((x>>d)&1) 
			return 1LL*dfs(tr[u].to[0], tr[v].to[1], d-1)*dfs(tr[u].to[1], tr[v].to[0], d-1)%mod;//两组的子集可以各自组合
		else {
			int ret = upd(dfs(tr[u].to[0], tr[v].to[0], d-1)+dfs(tr[u].to[1], tr[v].to[1], d-1));
			ret=upd(ret+mod-1);//减去重复算的空集
			ret=upd(ret+1LL*upd(pw[tr[tr[u].to[0]].cnt]+mod-1)*upd(pw[tr[tr[u].to[1]].cnt]+mod-1)%mod);//保证左右子树各选至少一个数
			ret=upd(ret+1LL*upd(pw[tr[tr[v].to[0]].cnt]+mod-1)*upd(pw[tr[tr[v].to[1]].cnt]+mod-1)%mod);
			return ret;
		}
	}
}

signed main() {
	read(n), read(x);
	pw[0]=1;
	for(int i = 1; i <= n; ++i)
		pw[i]=upd(pw[i-1]+pw[i-1]);
	gs=1;
	for(int i = 1; i <= n; ++i) {
		read(a);
		int now = 1;
		++tr[1].cnt;
		for(int j = 29; j >= 0; --j) {
			int& nxt = tr[now].to[(a>>j)&1];
			if(!nxt) nxt=++gs;
			now=nxt;
			++tr[now].cnt;
		}
	}
	write(upd(dfs(1, 1, 29)+mod-1), '\n');
	return 0;
}