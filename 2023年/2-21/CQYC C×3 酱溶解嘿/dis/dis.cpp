#include <bits/stdc++.h>
using namespace std;
int n, m, k[100005], pd[100005], dis[100005], tot, zhan[100005];
long long ans[100005];
vector <int> to[100005], pro;
vector <int> qwq;
char q;
void dfs(int x, int fa) {
	for(int y:to[x]) {
		if(y == fa || (pd[y] && x == y/2) || (pd[x] && x/2 == y)) continue;
		dis[y]=dis[x]+1;
		dfs(y, x);
	}
}
void getdis(int x, int fa) {
	zhan[++tot]=x;
	if(dis[x] >= 41) return ;
	for(int y:to[x]) {
		if(y == fa) continue;
		dis[y]=dis[x]+1;
		getdis(y, x);
	}
}
struct tree {
	long long tr[55], ret;
	void built() { memset(tr, 0, sizeof tr); } 
	void add(int x) {
		while(x <= 41)
			++tr[x], x=x+(x&(-x));
	}
	long long ask(int x) {
		ret=0;
		while(x >= 1)
			ret+=tr[x], x=x-(x&(-x));
		return ret;
	}
}A;
void ddfs(int x, int fa) {
	dis[x]=0;
	A.built();
	A.add(0+1);
	for(int y:to[x]) {
		if(y == fa) continue;
		dis[y]=1;
		getdis(y, x);
		for(int i = 1; i <= tot; ++i) 
			for(auto j:pro)
				if(dis[i] <= k[j])
					ans[j]+=A.ask(k[j]-dis[zhan[i]]+1);
		for(int i = 1; i <= tot; ++i) 
			A.add(dis[zhan[i]]+1);
		tot=0;
	}
	for(int y:to[x]) {
		if(y == fa) continue;
		ddfs(y, x);
	}
}
int main() {
	freopen("dis.in", "r", stdin);
	freopen("dis.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= n; ++i)
		to[i/2].push_back(i), to[i].push_back(i/2);
	if(n <= 50 && m <= 50) {
		for(int i = 1; i <= m; ++i) {
			scanf(" %c %d", &q, &k[i]);
			if(q == '-') 
				pd[k[i]]=1;
			else {
				int anss = 0;
				for(int o = 1; o <= n; ++o) {
					for(int j = 1; j <= n; ++j) 
						dis[j]=100000;
					dis[o]=0;
					dfs(o, o);
					for(int j = o+1; j <= n; ++j)
						anss+=(dis[j] <= k[i]);
				}
				printf("%d\n", anss);
			}
		}
	}
	for(int i = 1; i <= m; ++i) {
		scanf(" %c %d", &q, &k[i]);
		if(q == '-')
			return 0;
		else 
			pro.push_back(i);
	}
	ddfs(1, 1);
	for(int i = 1; i <= m; ++i) 
		printf("%lld\n", ans[i]);
	return 0;
} 
