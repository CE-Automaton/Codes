#include <bits/stdc++.h>
#define inf 1000000007 
using namespace std;
const int N = 5e5+5;
int n, m, pp, a[N], u, v, zhan[N], tot, dfn[(N<<1)], low[(N<<1)], cnt, hson[(N<<1)], top[(N<<1)],
ft[(N<<1)], siz[(N<<1)], dep[(N<<1)], dij[N];
vector <int> to[N], tr[(N<<1)];
queue <int> q;

template <typename T> inline void read(T& x) {
	x=0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int lne; char put[105];
template <typename T> inline void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne]^48), --lne;
}
void Tarjan(int x) {
	low[x] = dfn[x] = ++cnt;
	zhan[++tot] = x;
	for (int v : to[x]) {
		if (!dfn[v]) {
			Tarjan(v);
			low[x] = min(low[x], low[v]);
			if (low[v] == dfn[x]) {
				++pp;
				for (int xx = 0; xx != v; --tot) {
					xx = zhan[tot];
					tr[pp].push_back(xx);
					tr[xx].push_back(pp); 
				}
				tr[pp].push_back(x);
				tr[x].push_back(pp);
			}
		} else low[x] = min(low[x], dfn[v]);
	}
}
void srch(int x, int fa) {
	siz[x]=1;
	dep[x]=dep[fa]+1;
	ft[x]=fa;
	for(int i : tr[x])
		if(i != fa) {
			srch(i, x);
			siz[x]+=siz[i];
			if(siz[i] > siz[hson[x]])
				hson[x]=i;
		}
}
void renew(int x, int _top, int fa) {
	if(!x) return ;
	dfn[x]=++cnt;
	top[x]=(_top == -1 ? x : _top);
	renew(hson[x], top[x], x);
	for(int i : tr[x])
		if(i != fa && i != hson[x])
			renew(i, -1, x);
}
void srch2(int x, int fa) {
	siz[x]=1;
	dep[x]=dep[fa]+1;
	ft[x]=fa; 
	for(int i : to[x]) 
		if(i != fa) {
			srch2(i, x);
			siz[x]+=siz[i];
			if(siz[i] > siz[hson[x]])
				hson[x]=i;
		}
}
void renew2(int x, int _top, int fa) {
	if(!x) return ;
	dfn[x]=++cnt;
	top[x]=(_top == -1 ? x : _top);
	renew2(hson[x], top[x], x);
	for(int i : to[x])
		if(i != fa && i != hson[x])
			renew2(i, -1, x);
}
int check(int st, int fn, int x) {
	int pd = (st == 920 ? 1 : 0);
//	if(pd)
//		cout<<ft[st]<<" "<<ft[fn]<<"*\n";
	while(top[st] != top[fn]) {
		if(dep[top[st]] < dep[top[fn]]) swap(st, fn);
//		if(pd) cout<<dfn[top[st]]<<" "<<dfn[x]<<" "<<dfn[st]<<"!\n";
		if(dfn[top[st]] <= dfn[x] && dfn[x] <= dfn[st]) return 1;
		st=ft[top[st]];
	}
	if(dfn[st] > dfn[fn]) swap(st, fn);
//	if(pd)
//		cout<<dfn[st]<<" "<<dfn[x]<<" "<<dfn[fn]<<"!\n",
//		cout<<st<<" "<<x<<" "<<fn<<" "<<dep[st]<<" "<<dep[x]<<" "<<top[st]<<" "<<top[x]<<"???\n";
	if(dfn[st] <= dfn[x] && dfn[x] <= dfn[fn]) return 1;
	return 0;
}

int main() {
	freopen("sakura.in", "r", stdin);
	freopen("sakura.out", "w", stdout);
	read(n), read(m);
	pp = n;
	for(int i = 1; i <= n; ++i)
		read(a[i]), dij[i]=inf;
	for(int i = 1; i <= n; ++i)
		if(a[i] == i)
			dij[i]=0, q.push(i);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	if(m == n-1) {
		srch2(1, 1);
		renew2(1, -1, 1);
	}
	else {
		for(int i = 1; i <= n; ++i)
			if(!dfn[i]) 
				Tarjan(i), tot=0;
//		puts("!?");
		cnt=0;
		for(int i = 1; i <= pp; ++i)
			dfn[i]=siz[i]=0;
		srch(1, 0);
//		cout<<dep[255]<<ft[255]<<"!?\n";
//		puts("!?");
		renew(1, -1, 0);
	}
//	puts("!?");
	for(int i = 1; i <= n; ++i) 
		for(int j : to[i]) {
			if(dij[j] != inf) continue;
			if(check(a[j], a[i], i))
				dij[j]=1, q.push(j)/*, cout<<a[j]<<' '<<a[i]<<" "<<i<<"\n"*/;
		}
//	puts("!?");
	while(!q.empty()) {
		int it = q.front(); q.pop();
		for(int i : to[it]) 
			if(dij[i] == inf)
				dij[i]=dij[it]+1, q.push(i); 
	}
//	puts("!?");
	for(int i = 1; i <= n; ++i) 
		if(dij[i] == inf)
			putchar('-'), putchar('1'), putchar(' ');
		else
			write(dij[i]), putchar(' ');
	return 0;
}
