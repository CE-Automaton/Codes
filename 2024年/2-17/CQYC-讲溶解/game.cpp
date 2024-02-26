#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5, LG = 61;
int t, n, gs;
LL a[N], ans;
struct trie {
	int vis[2], cnt, siz;
	LL two, thr;
}tr[N*LG];

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
int crtn() {
	++gs, tr[gs].vis[0]=tr[gs].vis[1]=tr[gs].cnt=tr[gs].siz=0, tr[gs].two=tr[gs].thr=0;
	return gs;
}
void add(LL x) {
	int now = 0;
	// for(int i = 0; i < 60; ++i) 
	// 	debug((x>>i)&1);
	// debug('\n');
	for(int i = 0; i < 60; ++i) {
		int& to = tr[now].vis[((x>>i)&1)];
		if(!to) to=crtn();
		now=to;
	}
	++tr[now].cnt;
}
void dfs(int x, int dep) {//差的末尾有偶数个零时先手必败
	tr[x].siz=tr[x].cnt;
	if(tr[x].cnt >= 2)
		tr[x].two=1LL*tr[x].cnt*(tr[x].cnt-1)/2;
	if(tr[x].cnt >= 3)
		tr[x].thr=1LL*tr[x].cnt*(tr[x].cnt-1)/2*(tr[x].cnt-2)/3;
	if(tr[x].vis[0]) 
		dfs(tr[x].vis[0], dep+1), tr[x].siz+=tr[tr[x].vis[0]].siz, tr[x].two+=tr[tr[x].vis[0]].two, tr[x].thr+=tr[tr[x].vis[0]].thr;
	if(tr[x].vis[1]) 
		dfs(tr[x].vis[1], dep+1), tr[x].siz+=tr[tr[x].vis[1]].siz, tr[x].two+=tr[tr[x].vis[1]].two, tr[x].thr+=tr[tr[x].vis[1]].thr;
	if(tr[x].vis[0] && tr[x].vis[1] && dep%2 == 0) 
		ans+=1LL*tr[tr[x].vis[0]].siz*tr[tr[x].vis[1]].two+1LL*tr[tr[x].vis[0]].two*tr[tr[x].vis[1]].siz;
}

signed main() {
	File("game");
	read(t);
	while(t--) {
		tr[0].vis[0]=tr[0].vis[1]=tr[0].cnt=tr[0].siz=gs=0, tr[0].two=tr[0].thr=ans=0;
		read(n);
		for(int i = 1; i <= n; ++i)
			read(a[i]), add(a[i]);
		dfs(0, 0);
		ans+=tr[0].thr;//全相等特殊算
		write(1LL*n*(n-1)/2*(n-2)/3-ans, '\n');
	}
	return 0;
}
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症