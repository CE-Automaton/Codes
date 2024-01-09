#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 3e2+5;
int typ, t, n, fa[N], gs[N], l[N], r[N], ls[N], rs[N], k[N], siz[N], ans, ff[N], cnt[N];

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
int find(int x) {
	return (x == ff[x] ? x : ff[x]=find(ff[x]));
}
void check() {
	for(int i = 1; i <= n; ++i)
		ff[i]=i, cnt[i]=1;
	for(int i = 1; i <= n; ++i)
		k[i]=0;
	int pd = 1, rt = 0;
	for(int i = 1; i <= n; ++i) 
		if(fa[i]) {
			k[fa[i]]=max(k[fa[i]], i);
			int x = find(fa[i]), y = find(i);
			if(x == y)
				return ;
			if(cnt[x] < cnt[y]) swap(x, y);
			ff[y]=x;
			cnt[x]+=cnt[y];
		}
		else
			rt=i;
	if(gs[rt] == 0) return ;
	for(int i = 1; i <= n; ++i) 
		if((gs[i] != 0 && k[i] <= i) || gs[i] < l[i] || gs[i] > r[i]) {
			pd=0;
			break; 
		}
	for(int i = 1; i <= n; ++i) 
		if(gs[i] != 0)
			pd=upd(pd+pd);
	ans=upd(ans+pd);
}
void dfs(int x, int pd) {
	if(x == n+1) {
		check();
		return ;
	}
	if(pd) 
		fa[x]=0, dfs(x+1, 0);
	for(int i = 1; i <= n; ++i)
		if(gs[i] < r[i] && i != x)
			++gs[i], fa[x]=i, dfs(x+1, pd), fa[x]=0, --gs[i];
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(typ), read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			read(l[i]), read(r[i]), fa[i]=gs[i]=0;
		int gs = 0, ggs = 0, pp = 0;
		for(int i = 1; i <= n; ++i) {
			if(r[i] == 0)
				++gs;
			if(l[i] == 2)
				++ggs; 
			if(l[i] == 0)
				++pp;
		}
		if(typ == 8) {
			if(gs > 1) {
				puts("0");
				continue;
			}
			int sum = 1;
			for(int i = 1; i <= n-1; ++i)
				sum=upd(sum+sum);
			if(l[n] == 0)
				write(sum, '\n');
			else
				write(0, '\n');
			continue;
		}
		if(typ == 9 || (gs == 1 && ggs == 0)) {
			if(ggs) {
				puts("0");
				continue;
			}
			ans=1;
			for(int i = 1; i <= n-1; ++i)
				ans=upd(ans+ans);
			if(l[n] == 0)
				write(ans, '\n');
			else
				write(0, '\n');
			continue;
		}
		ans=0;
		dfs(1, 1);
		write(ans, '\n');
	} 
	return 0;
}
